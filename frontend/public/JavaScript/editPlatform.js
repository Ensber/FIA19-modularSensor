(function(){
    let name, abfrageinterval, farbe, platformId, nameInfo, abfrageintervalInfo, farbeInfo, idInfo, colorBox= undefined;

    let onLoad = function(){
        let editPlatformButtons = document.querySelectorAll('.editPlatformButton');
        Array.from(editPlatformButtons).forEach(function (element) {
            element.addEventListener('click', getEditPlatform);
        });
        document.getElementById('editPlatform').addEventListener('submit', editPlatform);
        document.getElementById('testColor').addEventListener('click', testColor);

        colorBox = document.getElementById('testColorBox');
        name = document.getElementById('name');
        nameInfo = document.getElementById('info_name');
        abfrageinterval = document.getElementById('abfrageinterval');
        abfrageintervalInfo = document.getElementById('info_abfrageinterval');
        farbe = document.getElementById('farbe');
        farbeInfo = document.getElementById('info_farbe');
        idInfo = document.getElementById('info_id');
    }

    let testColor = function(event){
        event.preventDefault();
        event.stopPropagation();
        colorBox.style.backgroundColor = 'white';
        colorBox.style.backgroundColor = farbe.value;
    }

    let editPlatform = function(event){
        event.preventDefault();
        event.stopPropagation();
        platformId = document.getElementById('editPlatform').getAttribute('data_edit_id');

        //TODO: Ajax Edit Platform + succes alert
        $.ajax({
            type: "POST",
            url: "editPlatform",
            data: {
                'abfrageinterval' : abfrageinterval.value,
                'farbe' : farbe.value,
                'name' : name.value,
                'id' : platformId
            },
            beforeSend: function () {
                resetErrors();
            },
            dataType: 'json',
            success: function (data) {
                location.reload();
                alert("Die Platform wurde Erfolgreich Bearbeitet");
            },
            error: function (data) {
                //alert("Die Platform kann nicht Bearbeitet werden!");
                for (let prop in data.responseJSON['errors']) {
                    if (prop !== 'id'){
                        document.getElementsByName(prop)[0].classList.add('errorInput');
                    }
                    document.getElementById('info_' + prop).textContent = data.responseJSON['errors'][prop];
                }
            }
        });
    }

    function resetErrors(){
        abfrageintervalInfo.textContent = "";
        nameInfo.textContent = "";
        farbeInfo.textContent = "";
        farbe.classList.remove('errorInput');
        name.classList.remove('errorInput');
        abfrageinterval.classList.remove('errorInput');
        idInfo.textContent = "";
    }
    let getEditPlatform = function(event){
        event.preventDefault();
        event.stopPropagation();
        let editTaskId = event.target.getAttribute('data-id');
        ajaxCallGetEditTask('getEditPlatform/' + editTaskId);
    }

    function ajaxCallGetEditTask(url){
        $.ajax({
            type: "EDIT",
            url: url,
            data: "",
            beforeSend: function () {
            },
            dataType: 'json',
            success: function (data) {
                createEditView(data);
            },
            error: function (data) {
                alert("Die Platform kann nicht Bearbeitet werden!");
            }
        });
    }

    let createEditView = function(data){
        resetErrors();
        console.log(data['platform']);
        let platform = data['platform'];
        document.getElementById('form_container').classList.remove('notVisible');
        document.getElementById('name').value = platform['name'];
        document.getElementById('abfrageinterval').value = platform['abfrageInterval'];
        document.getElementById('farbe').value = platform['farbe'];
        document.getElementById('editPlatform').setAttribute('data_edit_id', platform['id']);
        colorBox.style.backgroundColor = platform['farbe'];
    }

    window.addEventListener('load', onLoad);
})();