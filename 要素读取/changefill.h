//#ifndef CHANGEFILL_H
//#define CHANGEFILL_H

//#include <qgis/qgsproject.h>
//#include <qgis/qgsvectorlayer.h>
//#include <qgis/qgsvectorlayereditbuffer.h>
//#include <qgis/qgsgeometry.h>
//#include <qgis/qgssinglesymbolrenderer.h>
//#include <qgis/qgsfillsymbol.h>
//#include <qgis/qgsmultipoint.h>
//#include <qcolor.h>
//#include <qdebug.h>
//void convertBoundaryToPoints(QgsVectorLayer *layer)
//{
//    QgsVectorLayerEditBuffer *editBuffer = layer->editBuffer();

//    if (!editBuffer)
//    {
//        qDebug() << "Edit buffer not available!";
//        return;
//    }

//    QgsFeatureIterator it = layer->getFeatures();

//    QgsFeatureList features;
//    while (it.nextFeature())
//    {
//        QgsFeature feature = it.nextFeature();
//        QgsGeometry geometry = feature.geometry();

//        // Convert boundary to points
//        QgsMultiPoint boundaryPoints;
//        if (geometry.isGeosCollection())
//        {
//            for (int i = 0; i < geometry.numGeometries(); ++i)
//            {
//                QgsGeometry subGeometry = geometry.geometryN(i);
//                QgsMultiPoint subPoints = subGeometry.asMultiPoint();
//                boundaryPoints.addPoints(subPoints);
//            }
//        }
//        else
//        {
//            boundaryPoints = geometry.asMultiPoint();
//        }

//        // Create a new feature with the boundary points
//        QgsFeature newFeature;
//        newFeature.setGeometry(QgsGeometry(boundaryPoints));
//        newFeature.setAttributes(feature.attributes());

//        features.append(newFeature);
//    }

//    // Create a new memory layer for the points
//    QgsVectorLayer *pointsLayer = new QgsVectorLayer("Point?crs=" + layer->crs().authid(), "boundary_points", "memory");
//    QgsVectorLayerEditBuffer *pointsEditBuffer = pointsLayer->editBuffer();
//    pointsEditBuffer->addFeatures(features);
//    pointsLayer->updateExtents();

//    // Add points layer to the project
//    QgsProject::instance()->addMapLayer(pointsLayer);

//    // Set point symbol (optional)
//    QgsFillSymbol *fillSymbol = QgsFillSymbol::defaultSymbol(pointsLayer->geometryType());
//    fillSymbol->setColor(QColor(0, 0, 255, 255));  // Blue color

//    QgsSingleSymbolRenderer *renderer = new QgsSingleSymbolRenderer(fillSymbol);
//    pointsLayer->setRenderer(renderer);

//    // Trigger layer repaint
//    pointsLayer->triggerRepaint();

//    // Save project (if needed)
//    QgsProject::instance()->write();

//    // Clean up
//    delete renderer;
//}

//class ChangeFill
//{
//public:
//    ChangeFill();
//};

//#endif // CHANGEFILL_H
