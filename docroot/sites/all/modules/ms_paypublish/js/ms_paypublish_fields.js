(function ($) {
  $(document).ready(function() {
    ms_paypublish_update_fields();
    $("#edit-pid input:radio").click(function() {
      ms_paypublish_update_fields();
    });
    function ms_paypublish_update_fields() {
      var pid = $("#edit-pid input:radio:checked").val();
      // First, unblur all conditional fields
      $('.ms_paypublish_conditional_field').removeClass('ms_paypublish_field_blurred');
      // Get the value of the plan id and apply the blurred class to other fields
      $('.ms_paypublish_field_blur_when_' + pid).addClass('ms_paypublish_field_blurred');
    }
  });
})(jQuery);