#include "zstackviewparam.h"

ZStackViewParam::ZStackViewParam() :
  m_z(0), m_coordSys(NeuTube::COORD_RAW_STACK)
{
}

ZStackViewParam::ZStackViewParam(NeuTube::ECoordinateSystem coordSys) :
  m_z(0), m_coordSys(coordSys)
{
}

void ZStackViewParam::setZ(int z)
{
  m_z = z;
}

void ZStackViewParam::setViewPort(const QRect &rect)
{
  m_viewPort = rect;
}

void ZStackViewParam::setViewPort(int x0, int y0, int x1, int y1)
{
  m_viewPort.setTopLeft(QPoint(x0, y0));
  m_viewPort.setBottomRight(QPoint(x1, y1));
}

bool ZStackViewParam::operator ==(const ZStackViewParam &param) const
{
  return m_z == param.m_z && m_coordSys == param.m_coordSys &&
      m_viewPort == param.m_viewPort;
}

bool ZStackViewParam::operator !=(const ZStackViewParam &param) const
{
  return m_z != param.m_z || m_coordSys != param.m_coordSys ||
      m_viewPort != param.m_viewPort;
}

bool ZStackViewParam::contains(const ZStackViewParam &param) const
{
  if (m_z == param.m_z) {
    return m_viewPort.contains(param.m_viewPort);
  }

  return false;
}

void ZStackViewParam::resize(int width, int height)
{
  QPoint oldCenter = m_viewPort.center();
  m_viewPort.setSize(QSize(width, height));
  m_viewPort.moveCenter(oldCenter);
}
