todoApp.component('compteurComponent', {
    template: '<h3>{{ counter }}</h3>' +
        '<button ng-click="$ctrl.addToCounter()" type="button" class="btn btn-primary">Compteur</button>',
    controller: function ($scope) {

        this.load = function () {
            $scope.counter = localStorage.getItem('counter');
        }

        this.addToCounter = function () {
            if (!$scope.counter) {
                $scope.counter = localStorage.getItem('counter');
            }

            $scope.counter++;
            localStorage.setItem('counter', $scope.counter);
        }

        this.load();
    }
});