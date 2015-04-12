<div id="vendorRegistrationWrapper">
	<div id="vendorRegistration">
		<ul class="menu">
			<li><a href="/vendor-registration">Vendor<br/>Registration</a></li>
		</ul>
	</div>
</div>


<div id="navigationWrapper">
	<nav id="navigation">
        <div id="navigationLeft">
        	<?php print render($page['navigation']); ?>
        </div>
        <div id="navigationRight">
			<div id="user">
				<?php  print render($user_profile['user_picture']);?>
			</div>
            <div id="userMenu">
				<?php print render($page['user']); ?>
			</div>
        </div>
        <div class="clearfix"></div>
    </nav>
</div><!--end navigationWrapper-->



<div id="headerWrapper">
	<header id="header">
    	<div id="headerLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" height="90" width="312" /></a>
        </div>
        <div id="headerRight"><!--floats right -->
           	<?php print render($page['headerRight']); ?>
        </div>
        <div class="clearfix"></div>
    </header>
</div>


<section id="banner">
	<div id="filter">
		<?php print render($page['banner']); ?>
	</div>
</section>


<div id="contentWrapper">
	<div id="content">
        
        <section>
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
    	</section>		
    
    </div>
</div>

<div id="footerWrapper">
    <footer id="footer">
    	<div id="footerLeft1"><?php print render($page['footerLeft1']); ?></div>
        <div id="footerLeft2"><?php print render($page['footerLeft2']); ?></div>
        <div id="footerLeft3"><?php print render($page['footerLeft3']); ?></div>
        <div id="footerRight"><?php print render($page['footerRight']); ?></div>
        <div class="clearfix"></div>
    </footer>
</div>

<div id="copyWrapper">
    <div id="copy">
    	<div id="copyLeft">
    	<?php print render($page['copyLeft']); ?>
	<!--localtrove.com &copy; copyright 2013-->
	</div>
        <div id="copyCenter"></div>
        <div id="copyRight">
	<?php print render($page['copyRight']); ?>
	<!--Powered by Drupal, Hosted on Acquia, <a href="http://www.getJumpStartNow.com">Built by Jumpstart</a>-->
	</div>
    	<div class="clearfix"></div>
    </div>
</div>