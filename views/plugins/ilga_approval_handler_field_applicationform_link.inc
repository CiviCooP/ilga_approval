<?php
/**
 *  Drupal view handler for making te approval link
 *  with the correct parameters for autofilling
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_applicationform_link extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  private function currentUser(){
     civicrm_initialize();
     $session = CRM_Core_Session::singleton();
     return $session->get('userID');
  }

  function render($values) {

     $key = "-{$values->civicrm_contact_civicrm_relationship_1_id}-{$values->civicrm_contact_id}-";
     $nid = variable_get(ILGA_APPLICATION_WEBFORM_NID);
     $sid = ilga_approval_utils::webformSubmission($key);
     if($sid) {
         $url = "/print/{$nid}/submission/{$sid}";
         return l($values->civicrm_contact_display_name, $url);
     } else {
         return $values->civicrm_contact_display_name;
     }
  }

}