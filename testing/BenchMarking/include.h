#pragma once

constexpr long long iterations = 100000000;

/*
    Fill the section below for use in the bench marking
*/

#include "geometry/Vec.h"
#include "../src/geometry/Vec.cpp"

using namespace Geometry;

// Global variables
Vec2 a, b, c;
Vec3 a3, b3, c3;

volatile int x;
volatile int y;

float areaTotal, areaA, areaB, areaC;
float lA, lB, lC;

struct Cache1 {

    int difAB;
    int difBC;
    int difCA;

    float areaTotal;

    bool populated;

};

Cache1 cache1;

struct Cache2 {

    float i, j, k, p, m;

    int difXBA;
    int difXAB;
    int difYBA;
    int difYAB;

    bool populated;

};

Cache2 cache2;

void v1() {

    areaTotal = 0.5f * abs(
        (a.x * (b.y - c.y)) +
        (b.x * (c.y - a.y)) +
        (c.x * (a.y - b.y))
    );

    areaA = 0.5f * abs(
        (x * (b.y - c.y)) +
        (b.x * (c.y - y)) +
        (c.x * (y - b.y))
    );

    areaB = 0.5f * abs(
        (a.x * (y - c.y)) +
        (x * (c.y - a.y)) +
        (c.x * (a.y - y))
    );

    areaC = 0.5f * abs(
        (a.x * (b.y - y)) +
        (b.x * (y - a.y)) +
        (x * (a.y - b.y))
    );

    lA = areaA / areaTotal;
    lB = areaB / areaTotal;
    lC = areaC / areaTotal;
 
}

void v2() {

    if ( !cache1.populated ) {

        cache1.difAB = a.y - b.y;
        cache1.difBC = b.y - c.y;
        cache1.difCA = c.y - a.y;

        cache1.areaTotal = 0.5f * abs(
            (a.x * cache1.difBC) +
            (b.x * cache1.difCA) +
            (c.x * cache1.difAB)
        );

        cache1.populated = true;

    }

    areaA = 0.5f * abs(
        (x * (cache1.difBC)) +
        (b.x * (c.y - y)) +
        (c.x * (y - b.y))
    );

    areaB = 0.5f * abs(
        (a.x * (y - c.y)) +
        (x * (cache1.difCA)) +
        (c.x * (a.y - y))
    );

    areaC = 0.5f * abs(
        (a.x * (b.y - y)) +
        (b.x * (y - a.y)) +
        (x * (cache1.difAB))
    );

    lA = areaA / cache1.areaTotal;
    lB = areaB / cache1.areaTotal;
    lC = areaC / cache1.areaTotal;

}

void v3() {

    if ( !cache2.populated ) {

        cache2.j = b.y - ((b.x * c.y) / (float) c.x);

        cache2.p = c.y / (float) c.x;

        cache2.k = b.y - ((b.x * c.y) / (float) c.x);

        cache2.difXBA = b.x - a.x;
        cache2.difXAB = a.x - b.x;
        cache2.difYBA = b.y - a.y;
        cache2.difYAB = a.y - b.y;

        cache2.populated = true;

    }

    cache2.i = (
        ((x * cache2.difXAB) + (y * cache2.difYAB)) / 
        ((x * cache2.difXBA) + (y * cache2.difYAB))
    );

    cache2.m = (
        (1 / (y - (x * cache2.p))) *
        ((cache2.i * cache2.j) - cache2.k)
    );

    lA = 1 / cache2.m;

}


// Pre defined functions (fill as needed)
void init() {

    a.set(100, 100);
    b.set(200, 200);
    c.set(150, 300);

    a3.set(20, 30, 10);
    b3.set(-10, -20, 30);
    c3.set(10, -30, 50);

    x = 155;
    y = 179;

    cache1.populated = false;
    cache2.populated = false;

}

void run() {

    v3();

}

void cleanup() {

}
