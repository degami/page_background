(function($) {
  $(document).ready(function() {
    var page_background_cycle_options = {
      fx: Drupal.settings.page_background.fx,
      timeout: Drupal.settings.page_background.timeout,
      speed: Drupal.settings.page_background.speed,
      fit: Drupal.settings.page_background.fit,
      delay: Drupal.settings.page_background.delay,
      sync: Drupal.settings.page_background.sync,
      pager:  '#page_background_pager'
    };
    if(Drupal.settings.page_background.page_background_pager_generator == 'module'){
     page_background_cycle_options['pagerAnchorBuilder'] = function() {};
    }
    if(Drupal.settings.page_background.page_background_nav_links == true){
      page_background_cycle_options['prev'] = '#page_background_prev-slide';
      page_background_cycle_options['next'] = '#page_background_next-slide';
    }
    if(Drupal.settings.page_background.page_background_pauseonhover == true){
     page_background_cycle_options['pause'] = true;
     page_background_cycle_options['pauseOnPagerHover'] = true;
    }

    $('#page_background_container')
      .not('.processed')
      .cycle(page_background_cycle_options)
      .addClass('processed');
  });
})(jQuery);
