<?php
 function ilga_approval_views_data() {
   $data['ilga_approval']['table']['group'] = t('ILGA Custom');
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
   return $data;
 }

