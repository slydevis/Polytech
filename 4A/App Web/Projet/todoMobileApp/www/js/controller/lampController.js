app.controller('lampCtrl', ['$scope', function ($scope) {
    $scope.btnTxt = "Allumer";
    $scope.btnColor = "yellow lighten-1"
    $scope.textColor = "black-text"

    $scope.changeState = function () {
        var btn = document.getElementById('allumerBtn');
        var img = document.getElementById('myImage');

        if (btn.innerHTML === 'Allumer') {
            img.src = 'assets/ampoule_allume.png';
            $scope.btnTxt = 'Eteindre';
            $scope.btnColor = "blue-grey darken-1";
            $scope.textColor = "white-text"
        }
        else {
            img.src = 'assets/ampoule_eteinte.png';
            $scope.btnTxt = 'Allumer'
            $scope.btnColor = "yellow lighten-1";
            $scope.textColor = "black-text"
        }
    };
}]);