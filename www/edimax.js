"use strict";
function edimax() {
}

edimax.prototype.playVideo = function (url, options) {
	options = options || {};
	var handleSuccessCallback = function(playbackInfo) {
		if (options.successCallback && playbackInfo.isDone) {
			options.successCallback(playbackInfo);
		} else if (options.progressCallback && !playbackInfo.isDone) {
			options.progressCallback(playbackInfo);
		}
	}
	cordova.exec(handleSuccessCallback, options.errorCallback || null, "edimax", "playVideo", [url, options]);
};

edimax.prototype.playAudio = function (url, options) {
	options = options || {};
	var handleSuccessCallback = function(playbackInfo) {
		if (options.successCallback && playbackInfo.isDone) {
			options.successCallback(playbackInfo);
		} else if (options.progressCallback && !playbackInfo.isDone) {
			options.progressCallback(playbackInfo);
		}
	}
	cordova.exec(handleSuccessCallback, options.errorCallback || null, "edimax", "playVideo", [url, options]);
};

edimax.install = function () {
	if (!window.plugins) {
		window.plugins = {};
	}
	window.plugins.edimax = new edimax();
	return window.plugins.edimax;
};

cordova.addConstructor(edimax.install);