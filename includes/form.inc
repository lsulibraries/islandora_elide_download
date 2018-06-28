<?php

/**
 * @file
 * add checkbox to properties form for objects
 */

function islandora_elide_download_form($form, &$form_state) {
  $form['hide_download_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide Download Link'),
    '#default_value' => variable_get('islandora_elide_download_hide');
    '#description' => t('Check this option if you want the download link to be hidden from users'),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

function islandora_elide_download_form_submit($form, &$form_state) {
  variable_set('islandora_elide_download_hide', $form_state['values']['hide_download_link'] ? 1 : 0);
}
