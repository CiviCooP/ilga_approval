<?php
/**
 *  Drupal view handler - lookup for the comments of the current user
 *  in the approval
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_did_i_comment extends views_handler_field {

  public static function sql(){
    $config = ilga_approval_config::singleton();
  }

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function render($values) {
     $result = ilga_approval_utils::commentActivity($values->civicrm_contact_id);
     if($result){
       $answer = $result['approvedeny']?'Yes':'No';
       return "I said $answer ";
     } else {
       return 'Not Yet!';
     }
  }

}