<?php
/**
 * @file
 * Zen theme's implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $secondary_menu_heading: The title of the menu used by the secondary links.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 * - $page['bottom']: Items to appear at the bottom of the page below the footer.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see zen_preprocess_page()
 * @see template_process()
 */
?>

<div id="headerWrapper">
	<div id="header">
    	<div id="headerLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
        </div>
        <div id="headerRight"><!--floats right -->
            <ul class="menu">
            	<li><a href="/vendor-creation-and-registration">Vendors</a></li>
            </ul>
        </div>
        <div id="headerMiddle">
			<?php print render($page['headerRight']); ?>
        </div>
        <div class="clearfix"></div>
    </div>
</div>

<div id="navigationWrapper">
	<div id="navigation">
        <div id="navigationLeft">
        	<?php print render($page['navigation']); ?>
        </div>
        <div id="navigationRight">
        	<div id="search">
            	<?php print render($page['search']); ?>
            </div>
        </div>
        <div class="clearfix"></div>
    </div>
</div><!--end navigationWrapper-->


<div id="eventsNavWrapper">
	<div id="eventsNav">
        <?php print render($page['eventsNav']); ?>
        <div class="clearfix"></div>
    </div>
</div><!--end eventsNavWrapper-->


<div id="contentWrapper">
	<div id="content">
    	<!--if NO feature print contentLeft with class full-->
        <div id="contentLeft"<?php if( !($page['feature']) ):?><?php echo("class='full'") ;?><?php endif; ?>>
                <?php print render($title_prefix); ?>
				<?php if ($title): ?>
					<h1 style="display:none;"><?php print $title; ?></h1>
				<?php endif; ?>
				<?php print render($title_suffix); ?>
                <?php print $messages; ?>
				<?php if ($tabs = render($tabs)): ?>
					<div class="tabs"><?php print $tabs; ?></div>
				<?php endif; ?>
				<?php print render($page['help']); ?>
				<?php if ($action_links): ?>
					<ul class="action-links"><?php print render($action_links); ?></ul>
				<?php endif; ?>
                <?php print render($page['content']); ?>
        </div>

        <?php if ($page['feature']): ?>
        <div id="contentRight">
			<?php print render($page['feature']); ?>
        </div>
        <?php endif; ?>
        
        <div class="clearfix"></div>
        
        <div class="sidedish">
        	<?php print render($page['sidedish1']); ?>
        </div>
        
        <div class="sidedish">
        	<?php print render($page['sidedish2']); ?>
        </div>
        
        <div class="sidedish">
        	<?php print render($page['sidedish3']); ?>
        </div>
    			
    
        <div class="clearfix"></div>
    </div>
</div>

<div id="footerWrapper">
	<div id="footer">
    	<div id="footerLeft1"><?php print render($page['footerLeft1']); ?></div>
        <div id="footerLeft2"><?php print render($page['footerLeft2']); ?></div>
        <div id="footerLeft3"><?php print render($page['footerLeft3']); ?></div>
        <div id="footerRight"><?php print render($page['footerRight']); ?></div>
        <div class="clearfix"></div>
    </div>
</div>

<div id="copyWrapper">
	<div id="copy">
    	<div id="copyLeft">localtrove.com &copy; copyright 2012</div>
        <div id="copyCenter"></div>
        <div id="copyRight"><a href="http://www.getJumpStartNow.com">website design by Jump Start</a></div>
    	<div class="clearfix"></div>
    </div>
</div>