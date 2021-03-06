#include "Model.h"

ModelObj::ModelObj() : Model() {
    m_shape = null;
    m_keyFrame = null;
}

ModelObj::ModelObj(const std::string & file) : Model() {
    m_path = file;
    m_shape = new Shape();
    m_keyFrame = new KeyFrame;
    std::ifstream FILE;
    FILE.open(file.c_str());
    std::string line;
    while (std::getline(FILE, line)) {
        std::string lineType = readUntil(line, " ");
        if (lineType == "#");
        else if (lineType == "o")
            loadObject(line);
        else if (lineType == "v")
            loadVertexLine(line);
        else if (lineType == "vt")
            loadVertexTextureLine(line);
        else if (lineType == "vn")
            loadVertexNormalLine(line);
        else if (lineType == "ctp") // color texture path
            loadColorTexturePathLine(line);
        else if (lineType == "htp") // halo texture path
            loadColorTexturePathLine(line);
        else if (lineType == "btp") // bumpmap texture path
            loadColorTexturePathLine(line);
        else if (lineType == "f")
            loadFace(line);
        else
            loadObject(line);
    }
    FILE.close();

    //std::cout << "Start building ModelObj " << file << std::endl;
    if (buildModel()) {
        m_verticeData = m_shape->getVertice();
        m_normalData = m_shape->getNormal();
        m_textureData = m_shape->getTexture();
        m_verticeCount = m_shape->getVerticeCount();
        delete m_shape;
        delete m_keyFrame;
        load();
        //std::cout << "Success: loaded ModelObj " << file << std::endl;
    } else {
        std::cout << "Error: unable to load ModelObj " << file << std::endl;
    }
}

ModelObj::~ModelObj() {
}

void ModelObj::loadObject(std::string &line) {
    m_keyFrame->startVertice();
    m_keyFrame->startTexture();
}

void ModelObj::loadVertexLine(std::string &line) {
    float x = toFloat(readUntil(line, " "));
    float y = toFloat(readUntil(line, " "));
    float z = toFloat(line);

    m_keyFrame->addVertexData(x, y, z);
    //std::cout << "Load vertex : " << x << " " << y << " " << z << std::endl;
}

void ModelObj::loadVertexNormalLine(std::string &line) {
    float x = toFloat(readUntil(line, " "));
    float y = toFloat(readUntil(line, " "));
    float z = toFloat(line);

    m_keyFrame->addNormalData(x, y, z);
    //std::cout << "Load normal : " << x << " " << y << " " << z << std::endl;
}

void ModelObj::loadVertexTextureLine(std::string &line) {
    float x = toFloat(readUntil(line, " "));
    float y = toFloat(line);

    m_keyFrame->addTextureData(x, y);
    //std::cout << "Load texture : " << x << " " << y << std::endl;
}

void ModelObj::loadColorTexturePathLine(std::string &line) {
    m_colorTextureList.push_back(loadTexture(line));
}

void ModelObj::loadHaloTexturePathLine(std::string &line) {
    m_haloTextureList.push_back(loadTexture(line));
}

void ModelObj::loadBumpmapTexturePathLine(std::string &line) {
    m_bumpmapTextureList.push_back(loadTexture(line));
}

void ModelObj::loadFace(std::string &line) {
    std::string A, B, C;
    int av, an, at, bv, bn, bt, cv, cn, ct;

    A = readUntil(line, " ");
    B = readUntil(line, " ");
    C = line;

    av = toInt(readUntil(A, "/")) - 1;
    at = toInt(readUntil(A, "/")) - 1;
    an = toInt(A) - 1;

    bv = toInt(readUntil(B, "/")) - 1;
    bt = toInt(readUntil(B, "/")) - 1;
    bn = toInt(B) - 1;

    cv = toInt(readUntil(C, "/")) - 1;
    ct = toInt(readUntil(C, "/")) - 1;
    cn = toInt(C) - 1;

    m_shape->addFaceV(av, bv, cv);
    m_shape->addFaceN(an, bn, cn);
    m_shape->addFaceT(at, bt, ct);
}

bool ModelObj::buildModel() {
    m_shape->setVertice(m_keyFrame->getVertice());
    m_shape->setNormal(m_keyFrame->getNormal());
    m_shape->setTexture(m_keyFrame->getTexture());
    return true;
}
