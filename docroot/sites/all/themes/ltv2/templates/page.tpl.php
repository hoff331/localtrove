<div id="vendorRegistrationWrapper">
	<aside id="vendorRegistration">
		<?php print render($page['vendorReg']); ?>
	</aside>
	<div id="vendorRegistrationFlag">
		<ul class="menu">
			<li><a href="#">Vendor Registration</a></li>
		</ul>
	</div>
</div>


<div id="navigationWrapper">
	<nav id="navigation">
        <div id="navigationLeft">
        	<?php print render($page['navigationLeft']); ?>
        </div>
        <div id="navigationRight">
			<?php print render($page['navigationRight']); ?>
        </div>
        <div class="clearfix"></div>
    </nav>
</div><!--end navigationWrapper-->


<div id="headerWrapper">
	<header id="header">
    	<div id="headerLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/></a>
        </div>
        <div id="headerRight"><!--floats right -->
           	<?php print render($page['headerRight']); ?>
        </div>
        <div class="clearfix"></div>
    </header>
</div>


<section id="filterWrapper">
	<div id="intFilter">
		<?php print render($page['filter']); ?>
	</div>
</section>

<section id="bannerWrapper">
	<div id="intBanner">
		<?php print render($page['banner']); ?>
	</div>
</section>


<div id="contentWrapper">
	<div id="intContent">
		<div id="vendorHeader">
			<?php print render($page['vendorHeader']); ?>
		</div>
    	<!--if subNav, feature and nearbyMap print intContentLeft with class notFull-->
		<main id="intContentLeft"
		<?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?>
        <?php echo("class='notFull'"); ?>
        <?php endif; ?>
        >
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
        </main>
        
        <!--if subNav, feature or nearbyMap print intContentRight-->
		<?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?>
        <aside id="intContentRight">
        	
			<?php if ($page['subNav']): ?>
            <div id="subNav">
				<?php print render($page['subNav']); ?>
			</div>
            <?php endif; ?>
            
            <?php if ($page['addEvent']): ?>
            <div id="feature">
				<?php print render($page['addEvent']); ?>
			</div>
            <?php endif; ?>
            
			<?php if ($page['feature']): ?>
            <div id="feature">
				<?php print render($page['feature']); ?>
			</div>
            <?php endif; ?>
            
            <?php if ($page['nearbyMap']): ?>
            <div id="nearbyMap">
				<?php print render($page['nearbyMap']); ?>
			</div>
            <?php endif; ?>
            
        </aside>
        <?php endif; ?>
    			
    
        <div class="clearfix"></div>
    </div>
</div>


<div id="footerWrapper">
    <footer id="footer">
    	<div id="footerLeft"><?php print render($page['footerLeft']); ?></div>
        <div id="footerCenter"><?php print render($page['footerCenter']); ?></div>
        <div id="footerRight"><?php print render($page['footerRight']); ?></div>
        <div class="clearfix"></div>
    </footer>
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