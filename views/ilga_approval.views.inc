<?php
/**
 *  Add all the custom view handlers to the view builder
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */

 function ilga_approval_views_data() {
   $data['ilga_approval']['table']['group'] = t('ILGA Approval');
   $data['ilga_approval']['table']['join'] = array(
     // #global is a special flag which let's a table appear all the time.
     '#global' => array(),
   );

   $data['ilga_approval']['world_region'] = [
     'title' => t('World Region'),
     'help' => t('The world region connected to the country'),
     'field' => [
       'handler' => 'ilga_approval_handler_field_world_region',
       'click sortable' => TRUE,
     ],
   ];
   $data['ilga_approval']['media_links'] = [
     'title' => t('Media Links'),
     'help' => t('Website and Facebook Page'),
     'field' => [
       'handler' => 'ilga_approval_handler_field_media_links',
       'click sortable' => FALSE,
     ],
   ];
   $data['ilga_approval']['did_i_comment'] = [
     'title' => t('Did I comment'),
     'help' => t('Did I comment on this application'),
     'field' => [
       'handler' => 'ilga_approval_handler_field_did_i_comment',
       'click sortable' => FALSE,
     ],
   ];
   $data['ilga_approval']['approval_link'] = [
     'title' => t('Approval'),
     'help' => t('Link for finding the approval form'),
     'field' => [
       'handler' => 'ilga_approval_handler_field_approval_link',
       'click sortable' => FALSE,
     ],
   ];
   return $data;
 }

