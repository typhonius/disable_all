<?php

/**
 * @file Admin page for disable all module
 */

/**
 * Form callback to display submit buttons for disabling and enabling modules on the site.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function disable_all_admin_form($form, &$form_state) {
  $form = array();

  $disable_status = variable_get('disable_all_modules_disabled', FALSE);
  $affected = $disable_status ? unserialize(variable_get('disable_all_enabled_modules', serialize(array()))) : disable_all_get_disableable_modules();
  $title = $disable_status ? t('Modules to be enabled') : t('Modules to be disabled');

  $form['disable_all'] = array(
    'looka_looka' => array(
      '#type' => 'item',
      '#markup' => theme('item_list', array('title' => $title, 'items' => $affected)),
    ),
    'dooo_eeet' => array(
      '#type' => 'submit',
      '#value' => t('Dooo eeeet!'),
      '#access' => !$disable_status,
    ),
    'undooo_eeet' => array(
      '#type' => 'submit',
      '#value' => t('Undooo eeeet!'),
      '#access' => $disable_status,
    ),
  );

  return $form;
}

/**
 * Submit callback for disable_all_admin_form() to act upon the buttons pressed
 *
 * @see disable_all_admin_form()
 * @param $form
 * @param $form_state
 */
function disable_all_admin_form_submit($form, &$form_state) {
  $clicked = $form_state['clicked_button']['#parents'][0];

  switch ($clicked) {
    case 'dooo_eeet':
      disable_all_disable_all();
      break;
    case 'undooo_eeet':
      disable_all_enable_all();
      break;
  }

}

function disable_all_get_disableable_modules() {
  $system_modules = db_select('system', 's')
    ->fields('s', array('name', 'status', 'type', 'info'))
    ->condition('type', 'module')
    ->condition('status', 1)
    ->execute();

  $imma_disable_j00 = array();
  while ($result = $system_modules->fetchAssoc()) {
    $info = unserialize($result['info']);
    // Disabling required modules is superbad and let's not disable this module either.
    if (!isset($info['required']) && $result['name'] != 'disable_all'){
      $imma_disable_j00[] = $result['name'];
    }
  }
  
  sort($imma_disable_j00);
  return $imma_disable_j00;
}

/**
 * Function to disable all non-required modules.
 */
function disable_all_disable_all() {
  $imma_disable_j00 = disable_all_get_disableable_modules();

  module_disable($imma_disable_j00);
  variable_set('disable_all_modules_disabled', TRUE);
  // Save the modules that are disabled so we can go back to that state whenever.
  variable_set('disable_all_enabled_modules', serialize($imma_disable_j00));
  drupal_set_message(t('Lol disabled: ') . implode(', ', $imma_disable_j00));
}

/**
 * Function to enable all modules that have previously been disabled.
 */
function disable_all_enable_all() {
  $disabled_modules = unserialize(variable_get('disable_all_enabled_modules', serialize(array())));
  module_enable($disabled_modules);
  drupal_set_message(t('Just enabled these: ') . implode(', ', $disabled_modules));
  variable_del('disable_all_modules_disabled');
  variable_del('disable_all_modules_enabled');
}
