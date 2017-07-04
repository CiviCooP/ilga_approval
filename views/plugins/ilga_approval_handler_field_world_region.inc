<?php
/**
 * Created by PhpStorm.
 * User: Klaas
 * Date: 21-6-2017
 * Time: 17:46
 */
class ilga_approval_handler_field_world_region extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function wordRegionByCountry($country_id){
    $sql = 'select r.name from civicrm_worldregion r
            join   civicrm_country c on (c.region_id = r.id)
            where  c.id = %1';
    return CRM_Core_DAO::singleValueQuery($sql,array(
      '1' => array($country_id,'Integer'),
    ));

  }

  function render($values) {
    if(isset($values->civicrm_address_country_id)) {
      return $this->wordRegionByCountry($values->civicrm_address_country_id);
    } else {
      return 'No Address - No Region';
    }
  }

}