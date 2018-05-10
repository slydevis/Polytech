var app = angular.module('todoApp', ['ui.router', 'ui-notification']);

// Notification module setting
app.config(function (NotificationProvider) {
    NotificationProvider.setOptions({
        delay: 5000,
        startTop: 100,
        startRight: 10,
        verticalSpacing: 20,
        horizontalSpacing: 20,
        positionX: 'right',
        positionY: 'top',
        closeOnClick: true
    });
});