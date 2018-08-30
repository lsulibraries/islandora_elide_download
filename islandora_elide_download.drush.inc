<?php

/**
 * @file
 * Drush interface for hiding download link
 */

/**
 * Drush command declaration
 * implements hook_drush_command().
 * @return array
 * drush command data
 */

function islandora_elide_download_drush_command() {
  $items = array();
  $items['islandora-elide-download'] = array(
    'description' => 'Set wether an item is available for download',
    'examples' => array(
      'drush islandora-elide-download --user=admin elide --pid_file=/tmp/imagepids.txt',
      'drush islandora-elide-download --user=admin enable --pid_file=/tmp/imagepids.txt',
      'drush islandora-elide-download --user=admin elide --pid=islandora-photos:1',
    ),
    'aliases' => array('ied'),
    'arguments' => array(
      'op' => 'enable or elide',
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
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
  return $items;
}

/**
 * Naming is important alwasy use drush_mymodulename_whatever
 * @throws Exception
 * Either --op=elide or --op=enable.
 */

function drush_islandora_elide_download($op) {
  module_load_include('inc', 'islandora_elide_download', 'includes/utilities');
  $ops = array('enable', 'elide');
  if (!in_array($op, $ops)) {
    throw new Exception("Argument should be either: 'enable' or 'elide'");
  }
  $pids = islandora_elide_download_toggle_link_pid_or_pids();
  foreach ($pids as $pid) {
    $fn = 'islandora_elide_download_' . $op;
    $fn($pid);
    drush_print('Item: ' . $pid . ' was ' . $op . 'd', 0, NULL);
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
  foreach (array('pid', 'pid_file') as $option) {
    $$option = drush_get_option($option);
  }
  if ($pid Xor $pid_file) {
    return $pid ? array($pid) : explode(',', file_get_contents($pid_file));
  }
  else {
    throw new Exception("Must supply either --pid or --pid_file.");
  }
}
