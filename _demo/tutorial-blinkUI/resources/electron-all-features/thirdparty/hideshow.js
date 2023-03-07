/*
 * hideShow jQuery plugin
 * This plugin detects for visibility change on dom for attached elements.
 * Author : Pratik Soni
 * pratiksoni916@gmail.com
 */
"use strict";
((typeof jQuery === "function") && !((function($,w){
	$.fn.extend({
		hideShow : function(callback) {
			this.checkForVisiblilityChange(callback);
			return this;
		},

		checkForVisiblilityChange : function(callback) {

			if(!(this.length >>>0 ))
				return undefined;

			var elem,i=0;

			while ( ( elem = this[ i++ ] ) ) {
				var curValue = $(elem).is(":visible");

				(elem.lastVisibility === undefined) && (elem.lastVisibility = curValue);

				(curValue !== elem.lastVisibility) && (

					elem.lastVisibility = curValue,

					(typeof callback === "function") && (
						callback.apply(this, [new jQuery.Event('visibilityChanged'), curValue ? "shown" : "hidden"])
					),
					(function(elem, curValue, w){
						w.setTimeout(function(){
							$(elem).trigger('visibilityChanged',[curValue ? "shown" : "hidden"])
						},10)
					})(elem, curValue, w)
				)
			}

			(function(that, a, w){
				w.setTimeout(function(){
					that.checkForVisiblilityChange.apply(that,a);
				},10)
			})(this, arguments, w)
		}
	})
})(jQuery, window))) || console.error("hideShow plugin requires jQuery")
