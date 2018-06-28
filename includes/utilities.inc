<?php

/**
 * @file
 * utility functions to set pid in database or unset
 */

function islandora_elide_download_toggle_elide_link($pid) {
  db_insert('islandora_elide_download')
  ->fields(array('pid' => $pid)
  ->execute();
}

function islandora_elide_download_toggle_enable_link($pid) {
  db_delete('islandora_elide_download')
  ->condition('pid', $pid)
  ->execute();
}

function islandora_elide_download_is_hidden($pid) {
  $records = db_select('islandora_elide_download');
  ->condition('pid', $pid)
  ->execute();
  $hidden = $record->rowCount();
  return !$hidden;
}
