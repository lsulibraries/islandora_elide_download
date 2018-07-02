<?php

/**
 * @file
 * utility functions to set pid in database or unset
 */

function islandora_elide_download_elide($pid) {
  db_insert('islandora_elide_download')
  ->fields(array('id','pid'))
  ->values(array(
    'id' => NULL,
    'pid' => $pid,
  ))
  ->execute();
}

function islandora_elide_download_enable($pid) {
  db_delete('islandora_elide_download')
  ->condition('pid', $pid)
  ->execute();
}

function islandora_elide_download_is_listed($pid) {
  $records = db_select('islandora_elide_download', 'elide')
  ->fields('elide', array('id','pid'))
  ->condition('pid', $pid)
  ->execute();
  $hidden = $records->rowCount();
  return $hidden > 0;
}

function islandora_elide_download_submit_handler(&$form, &$form_state) {
  $fn = 'islandora_elide_download_toggle_link';
  $arg = $form_state['input']['toggle_elide_dl'] ? 'elide': 'enable';
  $pid = $form_state['input']['pid'];
  $fn($arg,$pid);
}

function islandora_elide_download_toggle_link($op, $pid) {
  module_load_include('inc', 'islandora_elide_download', 'includes/utilities');
  $ops = array('enable', 'elide');
  $fn = 'islandora_elide_download_toggle_' . $op .'_link' ;
  return $fn($pid);
}
