<div id="couponWrapper">
	<div id="printCoupon">
    	<div id="printCouponLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" height="90" width="312" /></a>
    	</div>
        <div id="printCouponRight">
        	<a href="javascript:window.print()"><img src="/sites/all/themes/localtrove/images/printCoupon.jpg" alt="print coupon"/></a>
        </div>
        <div class="clearfix"></div>
    </div>
	
	<?php global $user; //Load currently logged in user ?>
	<?php if ($user->uid == 0): ?>
    <div id="coupon">
        <h1>Sorry, you must be logged in to access LocalTrove.com coupons.</h1>
        <p>Don't worry, its free to <a href="/user/register">register</a>!</p>
        <p>If you are registered, please <a href="/user">log in</a>.</p>
    </div>
    <?php else: ?>
    <div id="coupon">
		<?php print render($title_prefix); ?>
        <?php if ($title): ?>
            <h1>LocalTrove.com Coupon: <?php print $title; ?></h1>
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
        <div class="clearfix"></div>
    </div>
    <?php endif; ?>


	<div id="disclaimer">
    	<p>To redeem, print or open coupon in a mobile browser and present to vendor prior to purchasing.</p>
    	<p>LocalTrove.com does not endorse this business nor is it liable for any issues related to redeeming this coupon. Please read our <a href="/node/22" target="_new">Terms of Service</a>.</p>
    </div>

</div>