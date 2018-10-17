<?php

/**
 *  Drupal view handler for making te approval link
 *  with the correct parameters for autofilling
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_applicationform_link extends views_handler_field
{

    /**
     * Just the contructor
     */
    function construct()
    {
        parent::construct();
    }

    /**
     * do nothing -- to override the parent query.
     */
    function query()
    {
        // do nothing -- to override the parent query.
    }

    /**
     * helper function to return the current Civi user (the user that is logged in)
     * TODO move this function to the utils class
     * @return mixed
     */
    private function currentUser()
    {
        civicrm_initialize();
        $session = CRM_Core_Session::singleton();
        return $session->get('userID');
    }

    /**
     * @param $values
     * @return string
     */
    function render($values)
    {

        $key = "-{$values->civicrm_contact_civicrm_relationship_1_id}-{$values->civicrm_contact_id}-";
        $nid = variable_get(ILGA_APPLICATION_WEBFORM_NID);
        $sid = ilga_approval_utils::webformSubmission($key,$nid);
        // if the english submission cannot be found - searcg for the spanish one
        if(empty($sid)){
          $nid = variable_get(ILGA_APPLICATION_WEBFORM_NID_SP);
          $sid = ilga_approval_utils::webformSubmission($key,$nid);
        }
        if ($sid) {
            $url = "/print/{$nid}/submission/{$sid}";
            return l($values->civicrm_contact_display_name, $url, ['attributes' => ['target' => '_blank']]);
        } else {
            return $values->civicrm_contact_display_name;
        }
    }

}