<?php

/**
 * @file
 * utility functions to set pid in database or unset
 */

/**
 * @param string
 * string value of object pid
 * add pid to db, and rebuild theme cache
 */

function islandora_elide_download_elide($pid) {
  db_insert('islandora_elide_download')
  ->fields(array('id','pid'))
  ->values(array(
    'id' => NULL,
    'pid' => $pid,
  ))
  ->execute();
  drupal_theme_rebuild();
  //db_query("DELETE FROM {cache};"); //less targeted rebuild of cache
}

/**
 * @param string
 * string value of object pid
 * remove any match of pid from db, and rebuild theme cache
 */

function islandora_elide_download_enable($pid) {
  db_delete('islandora_elide_download')
  ->condition('pid', $pid)
  ->execute();
  drupal_theme_rebuild();
}

/**
 * @param string
 * string value of object pid
 * confirm existance of pid in db
 * @return bool
 * false if not in db, true if in db at least once
 */

function islandora_elide_download_is_listed($pid) {
  $records = db_select('islandora_elide_download', 'elide')
  ->fields('elide', array('id','pid'))
  ->condition('pid', $pid)
  ->execute();
  $hidden = $records->rowCount();
  return $hidden > 0;
}

/**
 * submit handler for objcet properties form.
 * checks form for checkbox option,
 * apply checkbox operation to object by calling toggle_link function
 */

function islandora_elide_download_submit_handler(&$form, &$form_state, $form_id) {
  if ($form_id == 'islandora_object_properties') {
    $fn = 'islandora_elide_download_toggle_link';
    $arg = $form_state['input']['toggle_elide_dl'] ? 'elide': 'enable';
    $pid = $form_state['input']['pid'];
    $fn($arg,$pid);
  }
}

/**
 * @param string
 * which operation to call 'elide' or 'enable'
 * @param string
 * pid of object to apply operation
 */

function islandora_elide_download_toggle_link($op, $pid) {
  module_load_include('inc', 'islandora_elide_download', 'includes/utilities');
  $ops = array('enable', 'elide');
  $fn = 'islandora_elide_download_' . $op ;
  return $fn($pid);
}

// function islandora_elide_download_submit_handler(&$form, &$form_state $form_id) {
//   $fn = 'islandora_elide_download_toggle_link';
//   $arg = $form_state['input']['toggle_elide_dl'] ? 'elide': 'enable';
//   $pid = $form_state['input']['pid'];
//  if form_id is ingest...
// if ($form_id == 'islandora_ingest_form') {
// foreach ($form_state['islandora']['objects'] as $obj) {
//   $array = (array)$obj;
//   $prefix = chr(0).'*'.chr(0);
//   $fn($arg,$array[$prefix.'objectId']);
// }
// }
//   $fn($arg,$pid);
// }
