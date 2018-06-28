<?php

/**
 * @file
 * Drush interface for hiding download link
 */

/**
 * Drush command declaration
 * @return array
 * drush command data
 */

function islandora_elide_download_toggle_link_drush_command() {
  $items = array();
  $items['islandora-elide-download-toggle-link'] = array(
    'description' => 'Set wether an item is available for download',
    'aliases' => array('iedtl'),
    'arguments' => array(
      'op' => 'Toggle link active or inactive',
    ),
    'options' => array(
      'pid_file' => array(
        'description' => dt('File of comma-separated pid strings to target.'),
        'required' => FALSE,
      ),
      'pid' => array(
        'description' => dt('Islandora pid to target.'),
        'required' => FALSE,
      ),
    ),
  );
}

/**
 *
 * @throws Exception
 * Either --op=elide or --op=enable.
 */

function islandora_elide_download_drush_toggle_link($op) {
  $ops = array('enable', 'elide');
  if (!in_array($op, $ops)) {
    throw new Exception("Argument should be either: 'enable' or 'elide'");
  }
  $pids = islandora_elide_download_toggle_link_pid_or_pids();
  foreach ($pids as $pid) {
    $fn = 'islandora_elide_download_toggle_link_' . $op;
    $fn($pid);
  }
}

/**
 * Return array of pids depending on drush option
 * @return array
 *
 * @throws Exception
 *   Either --pid or --pid_file not both
 */

function islandora_elide_download_toggle_link_pid_or_pids() {
  module_load_include('inc', 'islandora_elide_download', 'includes/utilities');
  foreach (array('pid', 'pid_file') as $option) {
    $option = drush_get_option($option);
  }
  if ($pid Xor $pid_file) {
    return $pid ? array($pid) : explode(',', file_get_contents($pid_file));
  }
  else {
    throw new Exception("Must supply either --pid or --pid_file.");
  }
}
