(function () {
    let begin, end, beginInfo, endInfo = undefined
    let onLoad = function () {
        document.getElementById('showData').addEventListener('submit', showData);
        begin = document.getElementById('begin');
        beginInfo = document.getElementById('info_begin');
        end = document.getElementById('end');
        endInfo = document.getElementById('info_end');
    }

    let showData = function (event) {
        event.preventDefault();
        event.stopPropagation();

        $.ajax({
            type: "POST",
            url: 'charts',
            data: {
                'begin': begin.value,
                'end': end.value
            },
            beforeSend: function () {
                begin.classList.remove('errorInput');
                end.classList.remove('errorInput');
                beginInfo.textContent = '';
                endInfo.textContent = '';
                document.getElementById("wait").classList.add("wait");
            },
            dataType: 'json',
            success: function (data) {
                document.getElementById("wait").classList.remove("wait");
                createDiagramm(data);
            },
            error: function (data) {
                document.getElementById("wait").classList.remove("wait");
                for (let prop in data.responseJSON['errors']) {
                    document.getElementsByName(prop)[0].classList.add('errorInput');
                    document.getElementById('info_' + prop).textContent = data.responseJSON['errors'][prop];
                }
            }
        });
    }

    function createDiagramm(data) {
        document.getElementById("charts_container").innerHTML = "";
        data['werte'].forEach(function (werte) {
            var timeFormat = 'DD/MM/YYYY/HH:mm';
            let dataset = [];
            let diagrammText = werte['Typ'];
            let counter1 = 0;
            let averageTableBody = "";
            if (werte['platform'] !== undefined) {
                werte['platform'].forEach(function (entry) {
                    let datas = [];
                    let counter2 = 0;
                    averageTableBody += "<tr><td>" + entry['name'] + "</td><td>" + entry['average'] + "</td></tr>";
                    if (entry['data'] !== undefined){
                        entry['data'].forEach(function (data) {
                            datas[counter2] = {
                                'x': data['x'],
                                'y': data['y']
                            }
                            counter2++;
                        })
                    }
                    dataset[counter1] = {
                        'label': entry['name'],
                        'data': datas,
                        'fill': false,
                        'borderColor': entry['color']
                    }
                    counter1++;
                })


                const config = {
                    type: 'line',
                    data: {
                        datasets: dataset
                    },
                    options: {
                        responsive: true,
                        title: {
                            display: true,
                            text: diagrammText
                        },
                        scales: {
                            xAxes: [{
                                type: "time",
                                distribution: "linear",
                                time: {
                                    format: timeFormat,
                                    tooltipFormat: 'DD/MM/HH:mm'
                                },
                                scaleLabel: {
                                    display: true,
                                    labelString: 'Zeit'
                                }
                            }],
                            yAxes: [{
                                scaleLabel: {
                                    display: true,
                                    labelString: diagrammText
                                }
                            }]
                        }
                    }
                };
                if(werte['platform'][0]['data'] !== undefined){
                $("#charts_container").append(
                    "<div class='type_container'>" +
                    "<div class='chart_box'> <canvas id=" + diagrammText + " width='3' height='1'></canvas> </div>" +
                    "<div class='average_box'><table class='pure-table'><thead><th>Platform</th><th>Durchschnitt</th></thead>" + averageTableBody + "</table></div>" +
                    "</div><hr>"
                )
                var ctx = document.getElementById(diagrammText).getContext("2d");

                    var myChart = new Chart(
                        ctx, config
                    );
                }

            }
        })

    }

    window.addEventListener('load', onLoad);

})();