todoApp.controller('lampCtrl', ['$scope', function ($scope) {
    $scope.btnTxt = "Allumer";
    $scope.btnColor = "btn-warning"

    $scope.changeState = function () {
        var btn = document.getElementById('allumerBtn');
        var img = document.getElementById('myImage');

        if (btn.innerHTML === 'Allumer') {
            img.src = 'assets/ampoule_allume.png';
            $scope.btnTxt = 'Eteindre';
            $scope.btnColor = "btn-dark";
        }
        else {
            img.src = 'assets/ampoule_eteinte.png';
            $scope.btnTxt = 'Allumer'
            $scope.btnColor = "btn-warning";
        }
    };
}]);