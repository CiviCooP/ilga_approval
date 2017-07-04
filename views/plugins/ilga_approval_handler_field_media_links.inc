<?php
/**
 * Created by PhpStorm.
 * User: Klaas
 * Date: 21-6-2017
 * Time: 17:46
 */
class ilga_approval_handler_field_media_links extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function findMediaUrl($contact_id,$type){
    try {
      $url = civicrm_api3('Website', 'getvalue', [
        'return' => "url",
        'contact_id' => $contact_id,
        'website_type_id' => $type,
      ]);
      return $url;
    } catch (CiviCRM_API3_Exception $ex) {

    }
  }

  function render($values) {
    if(isset($values->civicrm_contact_id)){
      $mainsite = $this->findMediaUrl($values->civicrm_contact_id,'Main');
      $facebook =  $this->findMediaUrl($values->civicrm_contact_id,'Facebook');
      return l($mainsite,$mainsite).'</br>'.l($facebook,$facebook);
    } else {
      return 'No CiviCRM Contact Id';
    }
  }

}