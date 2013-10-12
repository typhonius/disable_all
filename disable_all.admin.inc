<?php

/**
 * @file Admin page for disable all module
 */

function disable_all_admin_form($form, &$form_state) {
  $form = array();

  $enabled_modules = module_list();

  $form['disable_all'] = array(
    'enabled_modules' => array(
      '#type' => 'hidden',
      '#value' => serialize($enabled_modules),
    ),
    'dooo_eeet' => array(
      '#type' => 'submit',
      '#value' => t('Dooo eeeet!'),
    ),
    'undooo_eeet' => array(
      '#type' => 'submit',
      '#value' => t('Undooo eeeet!'),
    ),
  );

  return $form;
}

function disable_all_admin_form_submit($form, &$form_state) {
  $clicked = $form_state['clicked_button']['#parents'][0];

  switch ($clicked) {
    case 'dooo_eeet':
      variable_set('disable_all_modules_disabled', 1);
      variable_set('disable_all_enabled_modules', $form_state['values']['enabled_modules']);
      break;
    case 'undooo_eeet':
      variable_del('disable_all_modules_disabled');
      break;
  }

}