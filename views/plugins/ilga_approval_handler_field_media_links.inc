<?php

/**
 *  Drupal view handler for selecting facebook & website url
 *  (The normal CiviCRM website view type creates a double row)
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_media_links extends views_handler_field
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
     * @param $contact_id
     * @param $type
     * @return array
     */
    function findMediaUrl($contact_id, $type)
    {
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

    /**
     * @param $values
     * @return string
     */
    function render($values)
    {
        if (isset($values->civicrm_contact_id)) {
            $mainsite = $this->findMediaUrl($values->civicrm_contact_id, 'Main');
            $facebook = $this->findMediaUrl($values->civicrm_contact_id, 'Facebook');
            return l($mainsite, $mainsite) . '</br>' . l($facebook, $facebook);
        } else {
            return 'No CiviCRM Contact Id';
        }
    }

}