jQuery(document).ready(function($) {
	// Code that uses jQuery's $ can follow here.
	$( "#user" ).click(function() {
		$( "#userMenu" ).toggle();
		$( "#user" ).toggleClass( "active");
	});
	
	$( "#vendorRegistrationFlag" ).click(function() {
		$( "#vendorRegistration" ).slideToggle( "slow", function() {
		// Animation complete.
		});
	});
	
});