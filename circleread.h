#ifndef CIRCLEREAD_H
#define CIRCLEREAD_H
#include "src/dl_creationadapter.h"
#include <QList>

class CIRCLEREAD : public DL_CreationAdapter
{
public:
    CIRCLEREAD();
    void readcircle(const char* filename);
    QList <DL_CircleData> circlelist;
    QList <DL_PolylineData> polylinelist;
    QList <DL_VertexData> vertexlist;

private:
   virtual void addText(const DL_TextData& data);
   virtual  void addCircle(const DL_CircleData& data);
   virtual void addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata);
    virtual void addPolyline(const DL_PolylineData &data);
    virtual void addVertex(const DL_VertexData & data);

};
#endif // CIRCLEREAD_H
