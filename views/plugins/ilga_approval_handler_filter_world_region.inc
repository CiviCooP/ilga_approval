<?php
/**
 *  Drupal view handler for making to filter on world region
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date august 2018
 * @license AGPL-3.0
 */

class ilga_approval_handler_filter_world_region extends views_handler_filter_in_operator{
    function construct() {
        parent::construct();
        if (!civicrm_initialize()) {
            return;
        }
    }

    function get_value_options() {
        $sql = 'SELECT id,name FROM civicrm_worldregion r';
        $dao = CRM_Core_DAO::executeQuery($sql);
        $options = [];
        while($dao->fetch()){
            $options[$dao->id]=$dao->name;
        }
        $this->value_options = $options;
    }

    function operators(){
        $operators = parent::operators();
        return $operators;
    }

    function op_simple()
    {
        if (empty($this->value)) {
            return;
        }
        $this->ensure_my_table();

        $clause = "civicrm_address.country_id is not null AND civicrm_address.country_id in (select id from {civicrm_country} where region_id in (" . implode(',',$this->value) . "))";

        $this->query->add_where_expression($this->options['group'], $clause);

    }

}