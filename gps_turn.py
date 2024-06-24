import math

def wgs84_to_gcj02(lon, lat):
    """
    WGS84坐标系转GCJ02坐标系
    :param lon: WGS84坐标系的经度
    :param lat: WGS84坐标系的纬度
    :return: GCJ02坐标系的经度和纬度
    """
    a = 6378245.0  # 添加这一行
    if out_of_china(lon, lat):
        return lon, lat
    else:
        dlat = _transformlat(lon - 105.0, lat - 35.0)
        dlon = _transformlon(lon - 105.0, lat - 35.0)
        radlat = lat / 180.0 * math.pi
        magic = math.sin(radlat)
        magic = 1 - 0.00669342162296594323 * magic * magic
        sqrtmagic = math.sqrt(magic)
        dlat = (dlat * 180.0) / ((a * (1 - 0.00669342162296594323)) / (magic * sqrtmagic) * math.pi)
        dlon = (dlon * 180.0) / (a / sqrtmagic * math.cos(radlat) * math.pi)
        gcj_lat = lat + dlat
        gcj_lon = lon + dlon
        return gcj_lon, gcj_lat

def _transformlat(x, y):
    ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * math.sqrt(abs(x))
    ret += (20.0 * math.sin(6.0 * x * math.pi) + 20.0 * math.sin(2.0 * x * math.pi)) * 2.0 / 3.0
    ret += (20.0 * math.sin(y * math.pi) + 40.0 * math.sin(y / 3.0 * math.pi)) * 2.0 / 3.0
    ret += (160.0 * math.sin(y / 12.0 * math.pi) + 320 * math.sin(y * math.pi / 30.0)) * 2.0 / 3.0
    return ret

def _transformlon(x, y):
    ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * math.sqrt(abs(x))
    ret += (20.0 * math.sin(6.0 * x * math.pi) + 20.0 * math.sin(2.0 * x * math.pi)) * 2.0 / 3.0
    ret += (20.0 * math.sin(x * math.pi) + 40.0 * math.sin(x / 3.0 * math.pi)) * 2.0 / 3.0
    ret += (150.0 * math.sin(x / 12.0 * math.pi) + 300.0 * math.sin(x * math.pi / 30.0)) * 2.0 / 3.0
    return ret

def out_of_china(lon, lat):
    """
    判断是否在国内
    :param lon:
    :param lat:
    :return:
    """
    if lon < 72.004 or lon > 137.8347:
        return True
    if lat < 0.8293 or lat > 55.8271:
        return True
    return False
