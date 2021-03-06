<?php

/**
 * Handles all configuration specific tasks. Used the singleton
 * pattern for efficient caching.
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_config
{

    static private $_singleton = NULL;

    private $_approveDenyCustomFields = array();
    private $_approveDenyCustomTable = NULL;
    private $_approvalActivityTypeId = NULL;
    private $_approvalCaseTypeId = NULL;

    public function __construct()
    {
        civicrm_initialize();
        $this->setUpApproveDeny();
        $this->setUpTypeIds();
    }

    /**
     * load the approve deny custom fields
     * @throws Exception
     */
    private function setUpApproveDeny()
    {
        try {
            $approveDenyCustomGroup = civicrm_api3('CustomGroup', 'getsingle', [
                'name' => 'Approve_Deny',
                'extends' => 'Activity'
            ]);
            $this->_approveDenyCustomTable = $approveDenyCustomGroup['table_name'];
        } catch (CiviCRM_API3_Exception $ex) {
            throw new Exception('Could not find a custom group with name Approve_Deny in ' . __METHOD__ . ', is required for Ilga Approval Processing. Contact your system administrator, 
        error from API CustomGroup getsingle: ' . $ex->getMessage());
        };
        // now get possible custom fields in the group
        try {
            $customFields = civicrm_api3('CustomField', 'get', array(
                'custom_group_id' => $approveDenyCustomGroup['id']));
            foreach ($customFields['values'] as $field) {
                $this->_approveDenyCustomFields [$field['name']] = $field['column_name'];
            }
        } catch (CiviCRM_API3_Exception $ex) {
        }
    }

    /**
     * load the type ids of the member application case and the member approval activity
     */
    private function setUpTypeIds()
    {

        try {
            $this->_approvalCaseTypeId = civicrm_api3('CaseType', 'getvalue', [
                'name' => "member_application",
                'return' => 'id'
            ]);
        } catch (CiviCRM_API3_Exception $ex) {
            drupal_set_message(t('Case type member_application not configured'), 'error');
        }

        try {
            $this->_approvalActivityTypeId = civicrm_api3('OptionValue', 'getvalue', array(
                'option_group_id' => "activity_type",
                'name' => "Member approval",
                'return' => 'value',
            ));
        } catch (CiviCRM_API3_Exception $ex) {
            drupal_set_message(t('Activity Type member_application not configured'), 'error');
        }

    }

    /**
     * @return array
     */
    public function getApproveDenyCustomFields()
    {
        return $this->_approveDenyCustomFields;
    }

    /**
     * @return null
     */
    public function getApproveDenyCustomTable()
    {
        return $this->_approveDenyCustomTable;
    }

    /**
     * @return null
     */
    public function getApprovalActivityTypeId()
    {
        return $this->_approvalActivityTypeId;
    }

    /**
     * @return null
     */
    public function getApprovalCaseTypeId()
    {
        return $this->_approvalCaseTypeId;
    }

    /**
     * Method to return singleton object
     *
     * @return object $_singleton
     * @access public
     * @static
     */
    public static function &singleton()
    {
        if (self::$_singleton === NULL) {
            self::$_singleton = new ilga_approval_config();
        }
        return self::$_singleton;
    }

}
