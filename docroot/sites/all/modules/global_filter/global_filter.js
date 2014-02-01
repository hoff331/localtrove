
(function($) {

  Drupal.behaviors.GlobalFilterSubmit = {
    attach: function(context, setting) {
      var filter_names = [setting.global_filter_1, setting.global_filter_2, setting.global_filter_3, setting.global_filter_4, setting.global_filter_5];
      // This may be called up to five times in one request, catering for up to
      // five global filter blocks on the same page.
      for (var i = 0; i < 5; i++) {
        if (filter_names[i] != undefined) {
          var claz = '.' + filter_names[i][0];
          var confirm_question = filter_names[i][1];
          var auto_submit = filter_names[i][2];
          var selectors = [claz, claz+' select', claz+' input:*[checked]'];
          var selection;
          for (var s=0; s < selectors.length; s++) {
            if (selection = $(selectors[s]).val()) {
              var selector = selectors[s];
              break;
            }
          }
          //alert(selector + ': ' + selection + ', ' + prompt_confirm + ', ' + auto_submit);
          $(s == 1 ? selector : claz).change(function() {
            if (confirm_question) {
              if (!confirm(Drupal.t(confirm_question))) {
                // Restore selection
                $(this).val(selection);
                return;
              }
              auto_submit = true;
            }
            if (auto_submit) {
              // Find enclosing form and auto-submit as soon as a new value is selected.
              for (var element = $(this).parent(); !element.is('form'); element = element.parent()) {}
              element.submit();
            }
          });
        }
      }
    }
  }

  Drupal.behaviors.GlobalFilterToggleViewOrFieldSelector = {
    attach: function(context, settings) {
      var viewSelectorDiv  = $('#global-filter-selector-view' ).parent();
      var fieldSelectorDiv = $('#global-filter-selector-field').parent();

      if ($('#global-filter-driver input[type="radio"]:checked').val() < 1) {
        viewSelectorDiv.hide();
      }
      else {
        fieldSelectorDiv.hide();
      }
      $('#global-filter-driver input[type="radio"]').change(function() {
        if ($(this).val() < 1) {
          viewSelectorDiv.hide();
          fieldSelectorDiv.show();
        }
        else {
          viewSelectorDiv.show();
          fieldSelectorDiv.hide();
        }
      });
    }
  }

  Drupal.behaviors.GlobalFilterLinkWidgetHandler = {
    attach: function(context, settings) {
      $('.global-filter-links li a').click(function(event) {
        event.preventDefault(); // prevent normal click action
        var id = $(this).attr('id');
        // id has format <field>:<value>
        var pos = id.indexOf(':');
        var field = id.substr(0, pos);
        var value = id.substr(pos + 1);
        var data = new Object;
        data['from_links_widget'] = field;
        data[field] = value;
        post_to('', data);
      });
    }
  }

})(jQuery);

function post_to(url, data) {
  jQuery.post(
    url,
    data,
    function(response){
      // Upon confirmation that the post was received, initiate a page refresh.
      // At this time the main module has already set the filter on the session.
      location.href = '';
    }
    //, 'json'
  );
}
