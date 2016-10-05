"use strict";
function rtspPlayer() {
}

rtspPlayer.prototype.playStream = function (url, options) {
    options = options || {};
    cordova.exec(options.successCallback || null, options.errorCallback || null, "rtspPlayer", "playRTSP", [url, options]);
};


rtspPlayer.install = function () {
    if (!window.plugins) {
        window.plugins = {};
    }
    window.plugins.rtspPlayer = new rtspPlayer();
    return window.plugins.rtspPlayer;
};

cordova.addConstructor(rtspPlayer.install);
