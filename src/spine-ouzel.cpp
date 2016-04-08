// Copyright (C) 2015 Elviss Strazdins

#include "spine-ouzel.h"
#include <fstream>
#include <spine/extension.h>

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

struct SpineTexture
{
    std::shared_ptr<ouzel::video::Texture> texture;
};

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
    SpineTexture* texture = new SpineTexture();

    texture->texture = ouzel::sharedEngine->getCache()->getTexture(path);
    self->rendererObject = texture;
    self->width = static_cast<int>(texture->texture->getSize().width);
    self->height = static_cast<int>(texture->texture->getSize().height);
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
    delete static_cast<SpineTexture*>(self->rendererObject);
}

char* _spUtil_readFile(const char* path, int* length)
{
    return _readFile(ouzel::sharedEngine->getFileSystem()->getPath(path).c_str(), length);
}

namespace spine
{
    SkeletonDrawable::SkeletonDrawable(spSkeletonData* skeletonData, spAnimationStateData* stateData):
        timeScale(1)
    {
        meshBuffer = ouzel::sharedEngine->getRenderer()->createMeshBuffer();
        meshBuffer->setIndexSize(sizeof(uint16_t));
        meshBuffer->setVertexAttributes(ouzel::video::VertexPCT::ATTRIBUTES);

        worldVertices = MALLOC(float, SPINE_MESH_VERTEX_COUNT_MAX);
        skeleton = spSkeleton_create(skeletonData);

        ownsAnimationStateData = stateData == 0;
        if (ownsAnimationStateData) stateData = spAnimationStateData_create(skeletonData);
        
        state = spAnimationState_create(stateData);

        _blendState = ouzel::sharedEngine->getCache()->getBlendState(ouzel::video::BLEND_ALPHA);
        _shader = ouzel::sharedEngine->getCache()->getShader(ouzel::video::SHADER_TEXTURE);

#ifdef OUZEL_PLATFORM_WINDOWS
        _uniModelViewProj = 0;
#else
        _uniModelViewProj = _shader->getVertexShaderConstantId("modelViewProj");
#endif

        _updateCallback = std::make_shared<ouzel::UpdateCallback>();
        _updateCallback->callback = std::bind(&SkeletonDrawable::update, this, std::placeholders::_1);
        ouzel::sharedEngine->scheduleUpdate(_updateCallback);
    }

    SkeletonDrawable::~SkeletonDrawable()
    {
        FREE(worldVertices);
        if (ownsAnimationStateData) spAnimationStateData_dispose(state->data);
        spAnimationState_dispose(state);
        spSkeleton_dispose(skeleton);

        ouzel::sharedEngine->unscheduleUpdate(_updateCallback);
    }

    void SkeletonDrawable::update(float delta)
    {
        spSkeleton_update(skeleton, delta);
        spAnimationState_update(state, delta * timeScale);
        spAnimationState_apply(state, skeleton);
        spSkeleton_updateWorldTransform(skeleton);
    }

    void SkeletonDrawable::draw()
    {
        Node::draw();

        ouzel::video::VertexPCT vertex;

        uint16_t currentVertexIndex = 0;
        std::vector<uint16_t> indices;
        std::vector<ouzel::video::VertexPCT> vertices;

        for (int i = 0; i < skeleton->slotsCount; ++i)
        {
            spSlot* slot = skeleton->drawOrder[i];
            spAttachment* attachment = slot->attachment;
            if (!attachment) continue;

            /*sf::BlendMode blend;
            switch (slot->data->blendMode) {
                case BLEND_MODE_ADDITIVE:
                    blend = BlendAdd;
                    break;
                case BLEND_MODE_MULTIPLY:
                    blend = BlendMultiply;
                    break;
                case BLEND_MODE_SCREEN: // Unsupported, fall through.
                default:
                    blend = BlendAlpha;
            }
            if (states.blendMode != blend) {
                target.draw(*vertexArray, states);
                vertexArray->clear();
                states.blendMode = blend;
            }*/

            SpineTexture* texture = 0;
            if (attachment->type == SP_ATTACHMENT_REGION)
            {
                spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;
                texture = (SpineTexture*)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
                spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, worldVertices);

                uint8_t r = static_cast<uint8_t>(skeleton->r * slot->r * 255);
                uint8_t g = static_cast<uint8_t>(skeleton->g * slot->g * 255);
                uint8_t b = static_cast<uint8_t>(skeleton->b * slot->b * 255);
                uint8_t a = static_cast<uint8_t>(skeleton->a * slot->a * 255);

                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;
                vertex.position.x = worldVertices[SP_VERTEX_X1];
                vertex.position.y = worldVertices[SP_VERTEX_Y1];
                vertex.texCoord.x = regionAttachment->uvs[SP_VERTEX_X1];
                vertex.texCoord.y = regionAttachment->uvs[SP_VERTEX_Y1];
                vertices.push_back(vertex);

                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;
                vertex.position.x = worldVertices[SP_VERTEX_X2];
                vertex.position.y = worldVertices[SP_VERTEX_Y2];
                vertex.texCoord.x = regionAttachment->uvs[SP_VERTEX_X2];
                vertex.texCoord.y = regionAttachment->uvs[SP_VERTEX_Y2];
                vertices.push_back(vertex);

                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;
                vertex.position.x = worldVertices[SP_VERTEX_X3];
                vertex.position.y = worldVertices[SP_VERTEX_Y3];
                vertex.texCoord.x = regionAttachment->uvs[SP_VERTEX_X3];
                vertex.texCoord.y = regionAttachment->uvs[SP_VERTEX_Y3];
                vertices.push_back(vertex);

                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;
                vertex.position.x = worldVertices[SP_VERTEX_X4];
                vertex.position.y = worldVertices[SP_VERTEX_Y4];
                vertex.texCoord.x = regionAttachment->uvs[SP_VERTEX_X4];
                vertex.texCoord.y = regionAttachment->uvs[SP_VERTEX_Y4];
                vertices.push_back(vertex);

                indices.push_back(currentVertexIndex + 0);
                indices.push_back(currentVertexIndex + 1);
                indices.push_back(currentVertexIndex + 2);
                indices.push_back(currentVertexIndex + 0);
                indices.push_back(currentVertexIndex + 2);
                indices.push_back(currentVertexIndex + 3);

                currentVertexIndex += 4;
            }
            else if (attachment->type == SP_ATTACHMENT_MESH)
            {
                spMeshAttachment* mesh = (spMeshAttachment*)attachment;
                if (mesh->verticesCount > SPINE_MESH_VERTEX_COUNT_MAX) continue;
                texture = (SpineTexture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject;
                spMeshAttachment_computeWorldVertices(mesh, slot, worldVertices);

                uint8_t r = static_cast<uint8_t>(skeleton->r * slot->r * 255);
                uint8_t g = static_cast<uint8_t>(skeleton->g * slot->g * 255);
                uint8_t b = static_cast<uint8_t>(skeleton->b * slot->b * 255);
                uint8_t a = static_cast<uint8_t>(skeleton->a * slot->a * 255);
                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;

                for (int t = 0; t < mesh->trianglesCount; ++t)
                {
                    int index = mesh->triangles[t] << 1;
                    vertex.position.x = worldVertices[index];
                    vertex.position.y = worldVertices[index + 1];
                    vertex.texCoord.x = mesh->uvs[index];
                    vertex.texCoord.y = mesh->uvs[index + 1];

                    indices.push_back(currentVertexIndex);
                    currentVertexIndex++;
                    vertices.push_back(vertex);
                }
                
            }
            else if (attachment->type == SP_ATTACHMENT_WEIGHTED_MESH)
            {
                spWeightedMeshAttachment* mesh = (spWeightedMeshAttachment*)attachment;
                if (mesh->uvsCount > SPINE_MESH_VERTEX_COUNT_MAX) continue;
                texture = (SpineTexture*)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject;
                spWeightedMeshAttachment_computeWorldVertices(mesh, slot, worldVertices);
                
                uint8_t r = static_cast<uint8_t>(skeleton->r * slot->r * 255);
                uint8_t g = static_cast<uint8_t>(skeleton->g * slot->g * 255);
                uint8_t b = static_cast<uint8_t>(skeleton->b * slot->b * 255);
                uint8_t a = static_cast<uint8_t>(skeleton->a * slot->a * 255);
                vertex.color.r = r;
                vertex.color.g = g;
                vertex.color.b = b;
                vertex.color.a = a;

                for (int t = 0; t < mesh->trianglesCount; ++t)
                {
                    int index = mesh->triangles[t] << 1;
                    vertex.position.x = worldVertices[index];
                    vertex.position.y = worldVertices[index + 1];
                    vertex.texCoord.x = mesh->uvs[index];
                    vertex.texCoord.y = mesh->uvs[index + 1];

                    indices.push_back(currentVertexIndex);
                    currentVertexIndex++;
                    vertices.push_back(vertex);
                }
            }

            if (texture && texture->texture)
            {
                ouzel::sharedEngine->getRenderer()->activateTexture(texture->texture, 0);
            }
        }

        meshBuffer->uploadIndices(indices.data(), static_cast<uint32_t>(indices.size()));
        meshBuffer->uploadVertices(vertices.data(), static_cast<uint32_t>(vertices.size()));

        if (ouzel::scene::LayerPtr layer = _layer.lock())
        {
            ouzel::sharedEngine->getRenderer()->activateBlendState(_blendState);
            ouzel::sharedEngine->getRenderer()->activateShader(_shader);

            ouzel::Matrix4 modelViewProj = layer->getCamera()->getViewProjection() * _transform;

            _shader->setVertexShaderConstant(_uniModelViewProj, { modelViewProj });

            ouzel::sharedEngine->getRenderer()->drawMeshBuffer(meshBuffer);
        }
    }
}
