import QtQuick 2.15

Item {
    property var points: []

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            if (points.length < 2)
                return

            // Найти min/max для масштабирования
            var minX = points[0].x, maxX = points[0].x
            var minY = points[0].y, maxY = points[0].y
            for (var i = 1; i < points.length; ++i) {
                minX = Math.min(minX, points[i].x)
                maxX = Math.max(maxX, points[i].x)
                minY = Math.min(minY, points[i].y)
                maxY = Math.max(maxY, points[i].y)
            }

            // Нарисовать линии
            ctx.beginPath()
            for (var i = 0; i < points.length; ++i) {
                var px = (points[i].x - minX) / (maxX - minX) * width
                var py = height - (points[i].y - minY) / (maxY - minY) * height
                if (i === 0)
                    ctx.moveTo(px, py)
                else
                    ctx.lineTo(px, py)
            }
            ctx.strokeStyle = "blue"
            ctx.lineWidth = 2
            ctx.stroke()
        }
    }

    onPointsChanged: canvas.requestPaint()
}
