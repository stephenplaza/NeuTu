#ifndef ZDVIDTILEENSEMBLE_H
#define ZDVIDTILEENSEMBLE_H

#include <vector>

#include "zstackobject.h"
#include "zdvidtileinfo.h"
#include "zdvidtarget.h"
#include "zdvidtile.h"

class ZStackView;

class ZDvidTileEnsemble : public ZStackObject
{
public:
  ZDvidTileEnsemble();
  ~ZDvidTileEnsemble();

  void clear();
  bool isEmpty() const;

  void display(ZPainter &painter, int slice, EDisplayStyle option) const;

  ZDvidTile* getTile(int resLevel, const ZDvidTileInfo::TIndex &index);

  void setDvidTarget(const ZDvidTarget &dvidTarget);
  void attachView(ZStackView *view);

  virtual const std::string& className() const;

  int getCurrentZ() const;

  ZStackView* getView() const;

  const ZDvidTarget& getDvidTarget() const {
    return m_dvidTarget;
  }

  void enhanceContrast(bool high);

private:
  void update(
      const std::vector<ZDvidTileInfo::TIndex>& tileIndices, int resLevel, int z);
  void updateContrast();

private:
  std::vector<std::map<ZDvidTileInfo::TIndex, ZDvidTile*> > m_tileGroup;
  ZDvidTileInfo m_tilingInfo;
  ZDvidTarget m_dvidTarget;
  ZStackView *m_view;
  bool m_highContrast;
};

#endif // ZDVIDTILEENSEMBLE_H
