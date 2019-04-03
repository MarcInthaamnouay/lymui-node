const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../index')

SegfaultHandler.registerHandler('xyz_crash.log')

describe('Creating Xyz from RGB', () => {
  it('Expect to create XYZ from RGB Object', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 50,
        g: 10,
        b: 95
      },
      output: 'xyz',
      profile: 'srgb'
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0.03488949569070142,
      y: 0.017213474858538254,
      z: 0.10972685952886765
    })
  })

  it('Expect to create XYZ from RGB Object with a clamp value of type ARGB', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 50,
        g: 10,
        b: 95
      },
      output: 'xyz',
      clamp: 10000,
      profile: 'adobe'
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0.0376,
      y: 0.0174,
      z: 0.1138
    })
  })

  it('Expect to create dark XYZ from RGB Object of type SRGB', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'xyz',
      profile: 'srgb',
      clamp: 10000
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    })
  })

  it('Expect to create dark XYZ from RGB Object of type adobe RGB', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'xyz',
      profile: 'srgb',
      clamp: 1000
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    })
  })

  it('Expect to create bright XYZ from RGB Object of type SRGB', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'xyz',
      profile: 'srgb',
      clamp: 10000
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0.9505,
      y: 1,
      z: 1.0888
    })
  })

  it('Expect to create bright XYZ from RGB Object of type adobe RGB', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'xyz',
      profile: 'adobe',
      clamp: 10000
    })

    expect(xyz.data).to.be.deep.equal({
      x: 0.9505,
      y: 1,
      z: 1.0888
    })
  })

  it('Expect to not clamp when clamp value is not a number', async () => {
    const xyz = await lib.fromRGB({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'xyz',
      profile: 'adobeRgb',
      clamp: 'foooo'
    })

    const x = Number.parseFloat(xyz.data.x).toFixed(4)
    const y = Number.parseFloat(xyz.data.y).toFixed(4)
    const z = Number.parseFloat(xyz.data.z).toFixed(4)

    expect(x).to.be.equal('0.9505')
    expect(y).to.be.equal('1.0000')
    expect(z).to.be.equal('1.0888')
  })
})

describe('Creating RGB from XYZ', () => {
  it('Expect to create RGB from XYZ sRGB', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0.0348,
        y: 0.0172,
        z: 0.1097
      },
      type: 'xyz',
      profile: 'srgb'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    })
  })

  it('Expect to create RGB from XYZ of type ARGB when no default profile is passed', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0.0376,
        y: 0.0173,
        z: 0.1138
      },
      type: 'xyz',
      profile: 'adobe'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    })
  })

  it('Expect to create dark RGB from XYZ Object of type SRGB', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      type: 'xyz',
      profile: 'srgb'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create dark RGB from Xyz Object of type adobe RGB', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      type: 'xyz',
      profile: 'adobe'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create bright RGB from XYZ Object of type SRGB', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0.9505,
        y: 1.0,
        z: 1.0887
      },
      type: 'xyz',
      profile: 'srgb'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to create bright RGB from Xyz Object of type adobe RGB', async () => {
    const rgb = await lib.toRGB({
      input: {
        x: 0.9505,
        y: 1.0,
        z: 1.0887
      },
      type: 'xyz',
      profile: 'adobe'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })
})