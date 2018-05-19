/* 
 * File:   Material.h
 * Author: ANTOINE
 *
 * Created on 6 février 2018, 15:34
 */
#pragma once

#ifndef MATERIAL_H
#define	MATERIAL_H

#include "Types.h"
#include "Texture.h"


struct MaterialComponent {
    bool hasColor;
    glm::vec4 color;
    bool hasTexture;
    Texture *texture;
    MaterialComponent(): hasColor(false), hasTexture(false), texture(null)
    {}
    void setColor(const glm::vec4 & color) {
        this->color = color;
        hasColor = true;
    }
    void setTexture(Texture * texture) {
        this->texture = texture;
        hasTexture = texture != null;
    }
};


class Material {
public:
    Material();
private:
    MaterialComponent albedo; // Texture0
    MaterialComponent normal; // Texture1
    MaterialComponent halo; // Texture2
};


#endif /* MATERIAL_H */
