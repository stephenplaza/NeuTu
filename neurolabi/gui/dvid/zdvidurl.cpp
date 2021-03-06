#include "zdvidurl.h"
#include <sstream>
#include "dvid/zdviddata.h"
#include "zstring.h"

const std::string ZDvidUrl::m_keyCommand = "key";
const std::string ZDvidUrl::m_keysCommand = "keys";
const std::string ZDvidUrl::m_keyRangeCommand = "keyrange";
const std::string ZDvidUrl::m_sparsevolCommand = "sparsevol";
const std::string ZDvidUrl::m_coarseSparsevolCommand = "sparsevol-coarse";
const std::string ZDvidUrl::m_infoCommand = "info";
const std::string ZDvidUrl::m_splitCommand = "split";
const std::string ZDvidUrl::m_coarseSplitCommand = "split-coarse";
const std::string ZDvidUrl::m_labelCommand = "label";
const std::string ZDvidUrl::m_roiCommand = "roi";

ZDvidUrl::ZDvidUrl()
{
}

ZDvidUrl::ZDvidUrl(
    const std::string &serverAddress, const std::string &uuid, int port)
{
  m_dvidTarget.set(serverAddress, uuid, port);
}

ZDvidUrl::ZDvidUrl(const ZDvidTarget &target)
{
  m_dvidTarget = target;
}

std::string ZDvidUrl::getNodeUrl() const
{
  return m_dvidTarget.getUrl();
}

std::string ZDvidUrl::getDataUrl(const std::string &dataName) const
{
  return m_dvidTarget.getUrl() + "/" + dataName;
}

std::string ZDvidUrl::getDataUrl(ZDvidData::ERole role) const
{
  return getDataUrl(ZDvidData::GetName(role));
}

std::string ZDvidUrl::getDataUrl(
    ZDvidData::ERole role, ZDvidData::ERole prefixRole,
    const std::string &prefixName)
{
  return getDataUrl(ZDvidData::GetName(role, prefixRole, prefixName));
}

std::string ZDvidUrl::getInfoUrl(const std::string &dataName) const
{
  return getDataUrl(dataName) + "/" + m_infoCommand;
}

std::string ZDvidUrl::getApiUrl() const
{
  return  "http://" + m_dvidTarget.getAddressWithPort() + "/api";
}

std::string ZDvidUrl::getHelpUrl() const
{
  return getApiUrl() + "/help";
}

std::string ZDvidUrl::getServerInfoUrl() const
{
  return getApiUrl() + "/server/info";
}

std::string ZDvidUrl::getSkeletonUrl() const
{
  return getSkeletonUrl(m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getSkeletonUrl(const std::string &bodyLabelName) const
{
  return getDataUrl(
        ZDvidData::GetName(ZDvidData::ROLE_SKELETON,
                           ZDvidData::ROLE_BODY_LABEL,
                           bodyLabelName));
}

std::string
ZDvidUrl::getSkeletonUrl(uint64_t bodyId, const std::string &bodyLabelName) const
{
  /*
  if (bodyId == 0) {
    return "";
  }
  */

  ZString str;
  str.appendNumber(bodyId);

  return GetKeyCommandUrl(getSkeletonUrl(bodyLabelName)) + "/" + str + "_swc";

#if 0
  ZString str;
  str.appendNumber(bodyId);

  return getSkeletonUrl(dataName) + "/" + str + ".swc";
#endif
}

std::string ZDvidUrl::getSkeletonUrl(uint64_t bodyId) const
{
  return getSkeletonUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getSkeletonConfigUrl(const std::string &bodyLabelName)
{
  return getSkeletonUrl(bodyLabelName) + "/key/config.json";
}

std::string ZDvidUrl::GetKeyCommandUrl(const std::string &dataUrl)
{
  return dataUrl + "/" + m_keyCommand;
}

std::string ZDvidUrl::getSparsevolUrl(const std::string &dataName) const
{
  return getDataUrl(dataName) + "/" + m_sparsevolCommand;
//      ZDvidData::GetName(ZDvidData::ROLE_SPARSEVOL);
}

std::string ZDvidUrl::getSparsevolUrl(int bodyId) const
{
  return getSparsevolUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getSparsevolUrl(int bodyId, int z) const
{
  ZString url = getSparsevolUrl(bodyId) + "?minz=";
  url.appendNumber(z);
  url += "&maxz=";
  url.appendNumber(z);

  return url;
}

std::string ZDvidUrl::getSparsevolUrl(
    int bodyId, const std::string &dataName) const
{
  if (bodyId < 0) {
    return "";
  }

  ZString str;
  str.appendNumber(bodyId);

  return getSparsevolUrl(dataName) + "/" + str;
}

std::string ZDvidUrl::getCoarseSparsevolUrl(const std::string &dataName) const
{
  return getDataUrl(dataName) + "/" + m_coarseSparsevolCommand;
//      ZDvidData::GetName(ZDvidData::ROLE_SPARSEVOL_COARSE);
}

std::string ZDvidUrl::getCoarseSparsevolUrl(
    uint64_t bodyId, const std::string &dataName) const
{
  if (bodyId == 0) {
    return "";
  }

  ZString str;
  str.appendNumber(bodyId);

  return getCoarseSparsevolUrl(dataName) + "/" + str;
}

std::string ZDvidUrl::getCoarseSparsevolUrl(uint64_t bodyId) const
{
  return getCoarseSparsevolUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getThumbnailUrl(uint64_t bodyId) const
{
  return getThumbnailUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getThumbnailUrl(const std::string &bodyLabelName) const
{
  return getDataUrl(
        ZDvidData::GetName(ZDvidData::ROLE_THUMBNAIL,
                           ZDvidData::ROLE_BODY_LABEL, bodyLabelName));
}

std::string ZDvidUrl::getThumbnailUrl(
    int bodyId, const std::string &bodyLabelName) const
{
  if (bodyId < 0) {
    return "";
  }

  ZString str;
  str.appendNumber(bodyId);

  return getKeyUrl(ZDvidData::GetName(ZDvidData::ROLE_THUMBNAIL,
                                      ZDvidData::ROLE_BODY_LABEL, bodyLabelName),
                   str + "_mraw");
//  return getThumbnailUrl(bodyLabelName) + "/" + str + ".mraw";
}

std::string ZDvidUrl::getRepoUrl() const
{
  return getApiUrl() + "/repo/" + m_dvidTarget.getUuid();
}

std::string ZDvidUrl::getInstanceUrl() const
{
  return getRepoUrl() + "/instance";
}


std::string ZDvidUrl::getSp2bodyUrl() const
{
  return getDataUrl(ZDvidData::GetName(ZDvidData::ROLE_SP2BODY));
}

std::string ZDvidUrl::getSp2bodyUrl(const std::string &suffix) const
{
  return getSp2bodyUrl() + "/" + suffix;
}

std::string ZDvidUrl::getGrayscaleUrl() const
{
  return getDataUrl(m_dvidTarget.getGrayScaleName());
//  return getDataUrl(ZDvidData::getName(ZDvidData::ROLE_GRAY_SCALE));
}

std::string ZDvidUrl::getGrayscaleUrl(int sx, int sy, int x0, int y0, int z0,
                                      const std::string &format)
const
{
  std::ostringstream stream;
  stream << "/raw/0_1/" << sx << "_" << sy << "/" << x0 << "_" << y0 << "_" << z0;
  if (!format.empty()) {
    stream << "/" << format;
  }
  return getGrayscaleUrl() + stream.str();
}

std::string ZDvidUrl::getGrayscaleUrl(int sx, int sy, int sz,
                                      int x0, int y0, int z0) const
{
  std::ostringstream stream;
  stream << "/raw/0_1_2/" << sx << "_" << sy << "_" << sz << "/"
         << x0 << "_" << y0 << "_" << z0;
  return getGrayscaleUrl() + stream.str();
}

std::string ZDvidUrl::getGrayScaleBlockUrl(
    int ix, int iy, int iz, int blockNumber) const
{
  std::ostringstream stream;
  stream << "/blocks/" << ix << "_" << iy << "_" << iz << "/" << blockNumber;
  return getGrayscaleUrl() + stream.str();
}

std::string ZDvidUrl::getLabels64Url() const
{
  return getDataUrl(m_dvidTarget.getLabelBlockName());
}

std::string ZDvidUrl::getLabels64Url(
    const std::string &name, int sx, int sy, int sz,
    int x0, int y0, int z0) const
{
  std::ostringstream stream;
  stream << "/raw/0_1_2/" << sx << "_" << sy << "_" << sz << "/"
         << x0 << "_" << y0 << "_" << z0;
  return getDataUrl(name) + stream.str();
}

std::string ZDvidUrl::getLabels64Url(int sx, int sy, int sz,
    int x0, int y0, int z0) const
{
  return getLabels64Url(m_dvidTarget.getLabelBlockName(), sx, sy, sz, x0, y0, z0);
}

std::string ZDvidUrl::getKeyUrl(const std::string &name, const std::string &key) const
{
  //new dvid api
  return GetKeyCommandUrl(getDataUrl(name)) + "/" + key;
}

std::string ZDvidUrl::getAllKeyUrl(const std::string &name) const
{
  return getDataUrl(name) + "/" + m_keysCommand;
}

std::string ZDvidUrl::getKeyRangeUrl(
    const std::string &name,
    const std::string &key1, const std::string &key2) const
{
  return getDataUrl(name) + "/" + m_keyRangeCommand + "/" + key1 + "/" + key2;

  /*
  std::string url = getDataUrl(name) + "/" + key1;
  if (!key2.empty()) {
    url += "/" + key2;
  }

  return url;
  */
}

std::string ZDvidUrl::getBodyAnnotationUrl(const std::string &bodyLabelName) const
{
  return getDataUrl(ZDvidData::GetName(ZDvidData::ROLE_BODY_ANNOTATION,
                                       ZDvidData::ROLE_BODY_LABEL,
                                       bodyLabelName));
}

std::string ZDvidUrl::getBodyAnnotationUrl(uint64_t bodyId, const std::string &bodyLabelName) const
{
  return GetKeyCommandUrl(getBodyAnnotationUrl(bodyLabelName)) + "/" +
      ZString::num2str(bodyId);
}

std::string ZDvidUrl::getBodyAnnotationUrl(uint64_t bodyId) const
{
  return getBodyAnnotationUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getBodyInfoUrl(const std::string &bodyLabelName) const
{
  return getDataUrl(ZDvidData::GetName(ZDvidData::ROLE_BODY_INFO,
                                       ZDvidData::ROLE_BODY_LABEL,
                                       bodyLabelName));
}

std::string ZDvidUrl::getBodyInfoUrl(uint64_t bodyId, const std::string &bodyName) const
{
  return getKeyUrl(ZDvidData::GetName(ZDvidData::ROLE_BODY_INFO,
                                      ZDvidData::ROLE_BODY_LABEL,
                                      bodyName), ZString::num2str(bodyId));
}

std::string ZDvidUrl::getBodyInfoUrl(uint64_t bodyId) const
{
  return getBodyInfoUrl(bodyId, m_dvidTarget.getBodyLabelName());
}

std::string ZDvidUrl::getBoundBoxUrl() const
{
  return getDataUrl(ZDvidData::ROLE_BOUND_BOX);
}

std::string ZDvidUrl::getBoundBoxUrl(int z) const
{
  return GetKeyCommandUrl(getBoundBoxUrl()) + "/" + ZString::num2str(z);
}

std::string ZDvidUrl::getBodyLabelUrl(const std::string &dataName) const
{
  return getDataUrl(dataName);
}

std::string ZDvidUrl::getBodyLabelUrl() const
{
  return getDataUrl(m_dvidTarget.getBodyLabelName());
  //return getDataUrl(ZDvidData::ROLE_BODY_LABEL);
}

#if 0
std::string ZDvidUrl::getBodyLabelUrl(const std::string &dataName,
    int x0, int y0, int z0, int width, int height, int depth) const
{
  std::ostringstream stream;
  stream << "/raw/0_1_2/" << width << "_" << height << "_" << depth << "/"
         << x0 << "_" << y0 << "_" << z0;
  return getBodyLabelUrl(dataName) + stream.str();
}

std::string ZDvidUrl::getBodyLabelUrl(
    int x0, int y0, int z0, int width, int height, int depth) const
{
  std::ostringstream stream;
  stream << "/raw/0_1_2/" << width << "_" << height << "_" << depth << "/"
         << x0 << "_" << y0 << "_" << z0;
  return getBodyLabelUrl() + stream.str();
}
#endif

std::string ZDvidUrl::getBodyListUrl(int minSize) const
{
  std::ostringstream stream;
  stream << "/sizerange/" << minSize;

  return getBodyLabelUrl() + stream.str();
}

std::string ZDvidUrl::getBodyListUrl(int minSize, int maxSize) const
{
  std::ostringstream stream;
  stream << "/sizerange/" << minSize << "/" << maxSize;

  return getBodyLabelUrl() + stream.str();
}

std::string ZDvidUrl::getSynapseListUrl() const
{
  return getBodyLabelUrl(m_dvidTarget.getBodyLabelName()) + "/allsynapse";
}

std::string ZDvidUrl::getSynapseAnnotationUrl(const std::string &name) const
{
  return  GetKeyCommandUrl(getBodyAnnotationUrl(m_dvidTarget.getBodyLabelName())) +
      "/" + name;
}

std::string ZDvidUrl::getSynapseAnnotationUrl() const
{
  return getSynapseAnnotationUrl("annotations-synapse");
}

std::string ZDvidUrl::getMergeUrl(const std::string &dataName) const
{
  return getDataUrl(dataName) + "/merge";
}

/*
std::string ZDvidUrl::getMergeOperationUrl(const std::string &dataName) const
{
  return getDataUrl(dataName);
}
*/

std::string ZDvidUrl::getMergeOperationUrl(const std::string &userName) const
{
  std::string key = m_dvidTarget.getLabelBlockName();
  if (!userName.empty()) {
    key += "_" + userName;
  }

  return GetKeyCommandUrl(
        getDataUrl(ZDvidData::GetName(ZDvidData::ROLE_MERGE_OPERATION))) + "/" +
      key;
}

std::string ZDvidUrl::getSplitUrl(
    const std::string &dataName, uint64_t originalLabel,
    const std::string &command) const
{
  std::ostringstream stream;
  if (command.empty()) {
    stream << getDataUrl(dataName) << "/" << originalLabel;
  } else {
    stream << getDataUrl(dataName) << "/" << command << "/" << originalLabel;
  }

  return stream.str();
}

std::string ZDvidUrl::getSplitUrl(
    const std::string &dataName, uint64_t originalLabel) const
{
  return getSplitUrl(dataName, originalLabel, m_splitCommand);
#if 0
  std::ostringstream stream;
  if (m_splitCommand.empty()) {
    stream << getDataUrl(dataName) << "/" << originalLabel;
  } else {
    stream << getDataUrl(dataName) << "/" << m_splitCommand << "/" << originalLabel;
  }

  return stream.str();
#endif
}

std::string ZDvidUrl::getCoarseSplitUrl(
    const std::string &dataName, uint64_t originalLabel) const
{
  if (!m_coarseSplitCommand.empty()) {
    return getSplitUrl(dataName, originalLabel, m_coarseSplitCommand);
  }

  return "";

#if 0
  std::ostringstream stream;
  if (m_coarseSplitCommand.empty()) {
    stream << getDataUrl(dataName) << "/" << m_coarseSplitCommand << "/"
           << originalLabel;
  }

  return stream.str();
#endif
}

/*
std::string ZDvidUrl::getMaxBodyIdUrl() const
{
  return getKeyUrl(ZDvidData::GetName(ZDvidData::ROLE_MAX_BODY_ID),
                   m_dvidTarget.getBodyLabelName());
}
*/

std::string ZDvidUrl::getTileUrl(const std::string &dataName) const
{
  return getDataUrl(dataName);
}

std::string ZDvidUrl::getBookmarkUrl() const
{
  return getDataUrl(ZDvidData::GetName(ZDvidData::ROLE_BOOKMARK));
}

std::string ZDvidUrl::getCustomBookmarkUrl(const std::string &userName) const
{
  return getKeyUrl(ZDvidData::GetName(ZDvidData::ROLE_BOOKMARK), userName);
}

std::string ZDvidUrl::getTileUrl(
    const std::string &dataName, int resLevel) const
{
  ZString url = getTileUrl(dataName);
  url += "/tile/xy/";
  url.appendNumber(resLevel);

  return url;
}

std::string ZDvidUrl::getTileUrl(
    const std::string &dataName, int resLevel, int xi0, int yi0, int z0) const
{
  ZString url = getTileUrl(dataName, resLevel);
  url += "/";
  url.appendNumber(xi0);
  url += "_";
  url.appendNumber(yi0);
  url += "_";
  url.appendNumber(z0);

  return url;
}

std::string ZDvidUrl::getRepoInfoUrl() const
{
  return getApiUrl() + "/repos/info";
}

std::string ZDvidUrl::getLockUrl() const
{
  return getNodeUrl() + "/lock";
}

std::string ZDvidUrl::getBranchUrl() const
{
  return getNodeUrl() + "/branch";
}

std::string ZDvidUrl::GetEndPoint(const std::string &url)
{
  std::string marker = "api/node/";
  std::string::size_type markerPos = url.find(marker) + marker.size();
  std::string::size_type uuidPos = url.find('/', markerPos);

  return url.substr(uuidPos);
}

std::string ZDvidUrl::getLocalBodyIdUrl(int x, int y, int z) const
{
  ZString url = getLabels64Url() + "/" + m_labelCommand + "/";
  url.appendNumber(x);
  url += "_";
  url.appendNumber(y);
  url += "_";
  url.appendNumber(z);

  return url;
}

std::string ZDvidUrl::getRoiUrl(const std::string &dataName) const
{
  return getDataUrl(dataName) + "/" + m_roiCommand;
}
