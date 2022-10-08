String root_html = "<!DOCTYPE html>\n\
\n\
<head>\n\
    <title>RGB Controller</title>\n\
    <style>\n\
        html,\n\
        body {\n\
            padding: 0;\n\
            margin: 0;\n\
            overflow: hidden;\n\
            font-family: monospace;\n\
            font-size: 1rem;\n\
        }\n\
\n\
        div.hexColorPicker {\n\
            width: fit-content;\n\
            margin: 0.75em auto;\n\
        }\n\
\n\
        span.condensed-line {\n\
            text-align: center;\n\
            display: block;\n\
            font-size: 20px;\n\
            line-height: 14.65px;\n\
            font-stretch: ultra-condensed;\n\
        }\n\
\n\
        span.colorHex {\n\
            cursor: pointer;\n\
        }\n\
\n\
        span.colorHex.color-selected {\n\
            -webkit-text-stroke: 1.15px black !important;\n\
        }\n\
\n\
        .noselect {\n\
            -webkit-touch-callout: none;\n\
            /* iOS Safari */\n\
            -webkit-user-select: none;\n\
            /* Safari */\n\
            -khtml-user-select: none;\n\
            /* Konqueror HTML */\n\
            -moz-user-select: none;\n\
            /* Old versions of Firefox */\n\
            -ms-user-select: none;\n\
            /* Internet Explorer/Edge */\n\
            user-select: none;\n\
            /* Non-prefixed version, currently\n\
		                                  supported by Chrome, Edge, Opera and Firefox */\n\
        }\n\
    </style>\n\
</head>\n\
\n\
<body>\n\
    <div class='hexColorPicker'>\n\
        <div id='output' class='noselect'></div>\n\
    </div>\n\
    <script>\n\
\n\
        const hexToRGB = (hex) => {\n\
            let h = hex.slice(hex.startsWith('#') ? 1 : 0);\n\
            if (h.length === 3) h = [...h].map(x => x + x).join('');\n\
            h = parseInt(h, 16);\n\
            return {\n\
                'r': (h >>> 16),\n\
                'g': ((h & 0x00ff00) >>> 8),\n\
                'b': ((h & 0x0000ff) >>> 0)\n\
            };\n\
        };\n\
\n\
        function handleRest(r, g, b) {\n\
            console.log(r);\n\
            console.log(g);\n\
            console.log(b);\n\
\n\
            var url = 'change';\n\
            var xhr = new XMLHttpRequest();\n\
            xhr.open('POST', url, true);\n\
            xhr.setRequestHeader('Content-Type', 'application/json');\n\
            // Converting JSON data to string\n\
            var data = JSON.stringify({ \"r\": r, \"g\": g, \"b\": b });\n\
\n\
            // Sending data with the request\n\
            xhr.send(data);\n\
\n\
        };\n\
\n\
        function generateColorPicker() {\n\
            const allColors = ['#003366', '#336699', '#3366CC', '#003399', '#000099', '#0000CC', '#000066', '#006666', '#006699', '#0099CC', '#0066CC', '#0033CC', '#0000FF', '#3333FF', '#333399', '#669999', '#009999', '#33CCCC', '#00CCFF', '#0099FF', '#0066FF', '#3366FF', '#3333CC', '#666699', '#339966', '#00CC99', '#00FFCC', '#00FFFF', '#33CCFF', '#3399FF', '#6699FF', '#6666FF', '#6600FF', '#6600CC', '#339933', '#00CC66', '#00FF99', '#66FFCC', '#66FFFF', '#66CCFF', '#99CCFF', '#9999FF', '#9966FF', '#9933FF', '#9900FF', '#006600', '#00CC00', '#00FF00', '#66FF99', '#99FFCC', '#CCFFFF', '#CCCCFF', '#CC99FF', '#CC66FF', '#CC33FF', '#CC00FF', '#9900CC', '#003300', '#009933', '#33CC33', '#66FF66', '#99FF99', '#CCFFCC', '#FFFFFF', '#FFCCFF', '#FF99FF', '#FF66FF', '#FF00FF', '#CC00CC', '#660066', '#336600', '#009900', '#66FF33', '#99FF66', '#CCFF99', '#FFFFCC', '#FFCCCC', '#FF99CC', '#FF66CC', '#FF33CC', '#CC0099', '#993399', '#333300', '#669900', '#99FF33', '#CCFF66', '#FFFF99', '#FFCC99', '#FF9999', '#FF6699', '#FF3399', '#CC3399', '#990099', '#666633', '#99CC00', '#CCFF33', '#FFFF66', '#FFCC66', '#FF9966', '#FF6666', '#FF0066', '#CC6699', '#993366', '#999966', '#CCCC00', '#FFFF00', '#FFCC00', '#FF9933', '#FF6600', '#FF5050', '#CC0066', '#660033', '#996633', '#CC9900', '#FF9900', '#CC6600', '#FF3300', '#FF0000', '#CC0000', '#990033', '#663300', '#996600', '#CC3300', '#993300', '#990000', '#800000', '#993333'];\n\
            // const hexUnicode = '⬢';\n\
            const hexUnicode = '\\u2B22';\n\
            var n = 0;\n\
            var hexNums = [7, 8, 9, 10, 11, 12];\n\
            var hexArrs = [];\n\
            var hexNum;\n\
\n\
            for (hexNum of hexNums) {\n\
                hexArr = [];\n\
                for (n = 0; n < hexNum; n++) hexArr.push(hexUnicode);\n\
                hexArrs.push(hexArr);\n\
            }\n\
            hexArr = [];\n\
            for (n = 0; n < 13; n++) hexArr.push(hexUnicode);\n\
            hexArrs.push(hexArr);\n\
            hexArr = [];\n\
            var hexNums2 = JSON.parse(JSON.stringify(hexNums));\n\
            hexNums2.reverse();\n\
            for (hexNum of hexNums2) {\n\
                hexArr = [];\n\
                for (n = 0; n < hexNum; n++) hexArr.push(hexUnicode);\n\
                hexArrs.push(hexArr);\n\
            }\n\
            var output = document.getElementById(\"output\");\n\
            for (var hexArrLine of hexArrs) {\n\
                var hexLine = '<span class=\"colorHex\">' + hexArrLine.join('</span><span class=\"colorHex\">') + '</span>';\n\
                output.insertAdjacentHTML('beforeend', '<span class=\"condensed-line\">' + hexLine + '</span>');\n\
            }\n\
\n\
            var colorHexs = document.getElementsByClassName('colorHex');\n\
            var h = 0;\n\
            for (var colorHex of colorHexs) {\n\
                colorHex['style']['webkit-text-fill-color'] = allColors[h];\n\
                colorHex['style']['color'] = allColors[h];\n\
                colorHex['style']['-webkit-text-stroke'] = '3.75px ' + allColors[h];\n\
\n\
                colorHex.setAttribute('data-hex', allColors[h]);\n\
                let rgbObj = hexToRGB(allColors[h]);\n\
                colorHex.setAttribute('data-r', rgbObj['r']);\n\
                colorHex.setAttribute('data-g', rgbObj['g']);\n\
                colorHex.setAttribute('data-b', rgbObj['b']);\n\
\n\
                colorHex.addEventListener('click', (evt) => {\n\
                    let hexSrcElement = evt.srcElement;\n\
\n\
                    let selectedColorHex = document.getElementsByClassName('color-selected');\n\
                    if (selectedColorHex.length > 0) {\n\
                        selectedColorHex[0].classList.remove('color-selected');\n\
                    }\n\
                    hexSrcElement.classList.add('color-selected');\n\
\n\
                    let dataset = hexSrcElement.dataset;\n\
                    let hexVal = dataset.hex;\n\
\n\
                    let rVal = dataset['r'];\n\
                    let gVal = dataset['g'];\n\
                    let bVal = dataset['b'];\n\
\n\
                    // Send of data to function\n\
                    handleRest(rVal, gVal, bVal);\n\
\n\
\n\
                }, false);\n\
                h++;\n\
            }\n\
        };\n\
\n\
        generateColorPicker();\n\
\n\
    </script>\n\
</body>";