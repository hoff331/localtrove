(function ($) {
  $(document).ready(function() {
    $("input#edit-same").click(function() {
      if ($("input#edit-same").is(':checked'))
      {
        // Checked, copy values
        $("input#edit-shipping-first-name").val($("input#edit-cc-first-name").val());
        $("input#edit-shipping-last-name").val($("input#edit-cc-last-name").val());
        $("input#edit-shipping-address1").val($("input#edit-billing-address1").val());
        $("input#edit-shipping-address2").val($("input#edit-billing-address2").val());
        $("input#edit-shipping-city").val($("input#edit-billing-city").val());
        $("input#edit-shipping-state").val($("input#edit-billing-state").val());
        $("input#edit-shipping-country").val($("input#edit-billing-country").val());
        $("input#edit-shipping-phone").val($("input#edit-billing-phone").val());
        $("input#edit-shipping-zip").val($("input#edit-billing-zip").val());
      }
      else
      {
        // Clear on uncheck
        $("input#edit-shipping-first-name").val("");
        $("input#edit-shipping-last-name").val("");
        $("input#edit-shipping-address1").val("");
        $("input#edit-shipping-address2").val("");
        $("input#edit-shipping-city").val("");
        $("input#edit-shipping-state").val("");
        $("input#edit-shipping-country").val("");
        $("input#edit-shipping-phone").val("");
        $("input#edit-shipping-zip").val("");
      }
    });
  });
})(jQuery);
