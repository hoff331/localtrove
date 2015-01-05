<section id="headerWrapper">
	<div id="header">
		<div id="headerLeft">
			<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
			<nav><?php print render($page['navigation']); ?></nav>
		</div>
		<div id="headerRight">
			<?php print render($page['headerRight']); ?>
		</div>
		<div class="clearfix"></div>
	</div>
</section><!--end headerWrapper-->


<main id="contentWrapper">
    <body id="intContent">
        <!--if subNav, feature and nearbyMap print intContentLeft with class notFull-->
		<div id="intContentLeft" <?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?><?php echo("class='notFull'"); ?><?php endif; ?>>
        		<?php if ($breadcrumb): ?>
					<?php print $breadcrumb; ?>
				<?php endif; ?>
                <?php print render($title_prefix); ?>
				<?php if ($title): ?>
					<h1><?php print $title; ?></h1>
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
        
        <!--if subNav, feature or nearbyMap print intContentRight-->
		<?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?>
        <div id="intContentRight">
        </div>
        <?php endif; ?>		
    
        <div class="clearfix"></div>
    </body>
</main>

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
    	<div id="copyLeft">
    	<?php print render($page['copyLeft']); ?>
	</div>
        <div id="copyCenter"></div>
        <div id="copyRight">
	<?php print render($page['copyRight']); ?>
	</div>
    	<div class="clearfix"></div>
    </div>
</div>
