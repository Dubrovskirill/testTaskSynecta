import QtQuick 2.15

Item {
    property var points: []

    // Отступы для осей и подписей
    property int marginLeft: 50
    property int marginBottom: 40
    property int marginTop: 20
    property int marginRight: 20

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            if (!points || points.length < 2)
                return

            var minX = points[0].x, maxX = points[0].x
            var minY = points[0].y, maxY = points[0].y
            for (var i = 1; i < points.length; ++i) {
                minX = Math.min(minX, points[i].x)
                maxX = Math.max(maxX, points[i].x)
                minY = Math.min(minY, points[i].y)
                maxY = Math.max(maxY, points[i].y)
            }

            var dx = (maxX - minX) * 0.05
            var dy = (maxY - minY) * 0.05
            minX -= dx; maxX += dx
            minY -= dy; maxY += dy

            var plotWidth = width - marginLeft - marginRight
            var plotHeight = height - marginTop - marginBottom

            function toCanvasX(x) {
                return marginLeft + (x - minX) / (maxX - minX) * plotWidth
            }
            function toCanvasY(y) {
                return marginTop + plotHeight - (y - minY) / (maxY - minY) * plotHeight
            }

            // Рисуем пунктирную сетку
            ctx.save()
            ctx.strokeStyle = "#cccccc"
            ctx.lineWidth = 1
            ctx.setLineDash([2, 4]) // Пунктир для сетки
            // Вертикальные линии (по X)
            for (var i = 0; i <= 5; ++i) {
                var xVal = minX + (maxX - minX) * i / 5
                var xPos = toCanvasX(xVal)
                ctx.beginPath()
                ctx.moveTo(xPos, marginTop)
                ctx.lineTo(xPos, marginTop + plotHeight)
                ctx.stroke()
            }
            // Горизонтальные линии (по Y)
            for (var j = 0; j <= 5; ++j) {
                var yVal = minY + (maxY - minY) * j / 5
                var yPos = toCanvasY(yVal)
                ctx.beginPath()
                ctx.moveTo(marginLeft, yPos)
                ctx.lineTo(marginLeft + plotWidth, yPos)
                ctx.stroke()
            }
            ctx.restore() // Восстанавливаем состояние после сетки

            // Рисуем оси
            ctx.save()
            ctx.strokeStyle = "#444"
            ctx.lineWidth = 1
            ctx.setLineDash([]) // Пытаемся сбросить пунктир
            ctx.beginPath()
            // X
            ctx.moveTo(marginLeft, marginTop + plotHeight)
            ctx.lineTo(marginLeft + plotWidth, marginTop + plotHeight)
            // Y
            ctx.moveTo(marginLeft, marginTop)
            ctx.lineTo(marginLeft, marginTop + plotHeight)
            ctx.stroke()
            ctx.restore()

            // Подписи осей
            ctx.save()
            ctx.fillStyle = "#222"
            ctx.font = "bold 12px sans-serif"
            ctx.textAlign = "center"
            ctx.fillText("Frequency (Hz)", marginLeft + plotWidth / 2, height - 10)
            ctx.translate(15, marginTop + plotHeight / 2)
            ctx.rotate(-Math.PI / 2)
            ctx.textAlign = "center"
            ctx.fillText("S11 LogMag", 0, 0)
            ctx.restore()

            // Метки на осях
            ctx.save()
            ctx.textAlign = "center"
            ctx.font = "10px sans-serif"
            ctx.setLineDash([]) // Пытаемся сбросить пунктир
            for (var i = 0; i <= 5; ++i) {
                var xVal = minX + (maxX - minX) * i / 5
                var xPos = toCanvasX(xVal)
                ctx.beginPath()
                ctx.moveTo(xPos, marginTop + plotHeight)
                ctx.lineTo(xPos, marginTop + plotHeight + 5)
                ctx.stroke()

                var xLabel = (xVal / 1e9).toFixed(2) + " GHz"
                ctx.fillText(xLabel, xPos, marginTop + plotHeight + 18)
            }

            ctx.textAlign = "right"
            for (var j = 0; j <= 5; ++j) {
                var yVal = minY + (maxY - minY) * j / 5
                var yPos = toCanvasY(yVal)
                ctx.beginPath()
                ctx.moveTo(marginLeft - 5, yPos)
                ctx.lineTo(marginLeft, yPos)
                ctx.stroke()
                ctx.fillText(yVal.toFixed(2), marginLeft - 8, yPos + 3)
            }
            ctx.restore()

            // Рисуем график
            ctx.save()
            ctx.strokeStyle = "blue"
            ctx.lineWidth = 2
            ctx.setLineDash([1000000]) // Длинный штрих для сплошной линии
            ctx.beginPath()
            for (var k = 0; k < points.length; ++k) {
                var px = toCanvasX(points[k].x)
                var py = toCanvasY(points[k].y)
                if (k === 0)
                    ctx.moveTo(px, py)
                else
                    ctx.lineTo(px, py)
            }
            ctx.stroke()
            ctx.restore()
        }
    }

    onPointsChanged: canvas.requestPaint()
}
