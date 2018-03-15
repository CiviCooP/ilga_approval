<?php

/**
 *  Drupal view handler for making for finding the world region
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_world_region extends views_handler_field
{

    /**
     * just the constructor
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
     * @param $country_id
     * @return null|string
     */
    function wordRegionByCountry($country_id)
    {
        $sql = 'SELECT r.name FROM civicrm_worldregion r
            JOIN   civicrm_country c ON (c.region_id = r.id)
            WHERE  c.id = %1';
        return CRM_Core_DAO::singleValueQuery($sql, array(
            '1' => array($country_id, 'Integer'),
        ));
    }

    /**
     * @param $values
     * @return null|string
     */
    function render($values)
    {
        if (isset($values->civicrm_address2_country_id)) {
            return $this->wordRegionByCountry($values->civicrm_address2_country_id);
        } else {
            return 'No Address - No Region';
        }
    }

}