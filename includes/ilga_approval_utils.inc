<?php

/**
 * Helper and utility functions
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_utils
{

    /**
     * sql template string to find the correct comment activity for case and an approver
     * (Case is found with contact id)
     * @return string
     */
    static public function commentActivitySQL()
    {
        $config = ilga_approval_config::singleton();
        return "SELECT act.id AS activity_id
          ,      ad.{$config->getApproveDenyCustomFields()['Can_this_organisation_become_an_ILGA_member']} approvedeny
          FROM   civicrm_case cas
          JOIN   civicrm_case_contact cc     ON (cc.case_id = cas.id AND cc.contact_id=%1)
          JOIN   civicrm_case_activity cact  ON (cact.case_id = cas.id) 
          JOIN   civicrm_activity      act   ON (act.id = cact.activity_id AND act.is_deleted=0 AND act.activity_type_id = {$config->getApprovalActivityTypeId()} AND act.is_current_revision=1 )
          JOIN   civicrm_activity_contact acc ON (acc.activity_id = act.id and acc.record_type_id=2 and acc.contact_id=%2)         
          JOIN   {$config->getApproveDenyCustomTable()} ad ON (ad.entity_id = act.id)
          where  cas.case_type_id = {$config->getApprovalCaseTypeId()}
         ";
    }

    /**
     * @param $contactId
     * @return array|bool the results of an approval activity
     */
    static public function commentActivity($contactId)
    {

        civicrm_initialize();
        $session = CRM_Core_Session::singleton();
        $dao = CRM_Core_DAO::executeQuery(ilga_approval_utils::commentActivitySQL(), array(
            '1' => array($contactId, 'Integer'),
            '2' => array($session->get('userID'), 'Integer')
        ));

        if ($dao->fetch()) {
            return array(
                'activity_id' => $dao->activity_id,
                'approvedeny' => $dao->approvedeny
            );
        } else {
            return FALSE;
        }
    }

    /**
     * @param $key
     * @return mixed
     */
    static public function webformSubmission($key,$nid)
    {
        $sid = db_query("
          SELECT ws.sid FROM {webform_civicrm_submissions} wcs
          JOIN {webform_submissions} ws ON (ws.sid = wcs.sid)
          WHERE nid=:nid AND wcs.contact_id LIKE :key
        ", array(
            ':key' => $key . '%',
            ':nid' => $nid
        ))->fetchField(0);
        return $sid;
    }

}