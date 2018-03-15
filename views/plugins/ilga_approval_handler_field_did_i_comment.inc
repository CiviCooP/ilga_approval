<?php

/**
 *  Drupal view handler - lookup for the comments of the current user
 *  in the approval
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_did_i_comment extends views_handler_field
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
     * @param $values
     * @return string
     */
    function render($values)
    {
        $result = ilga_approval_utils::commentActivity($values->civicrm_contact_id);
        if ($result) {
            $answer = $result['approvedeny'] ? 'Yes' : 'No';
            return "I said $answer ";
        } else {
            return 'Not Yet!';
        }
    }

}