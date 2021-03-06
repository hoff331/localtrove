<!DOCTYPE html>
<html <?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>

<!--[if lt IE 9]>
<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
<![endif]-->  
<!--Viewport-->
<meta name="viewport" content="width=device-width, initial-scale=1">
<!--Chrome Frame-->
<meta http-equiv="X-UA-Compatible" content="chrome=1" />
<!--BING-->
<meta name="msvalidate.01" content="188D09B632C56FE4E1514F30F48574A8" />
</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>