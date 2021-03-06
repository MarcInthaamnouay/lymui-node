const { expect } = require('chai')
const lib = require('../index')

describe('Creating tint from RGB', () => {
  it('Expect to create a tint from an RGB', async () => {
    const rgb = {
      r: 50,
      g: 100,
      b: 100
    }

    const tint = await lib.fromRGB({
      input: rgb,
      output: 'tint'
    })

    expect(tint.data).to.not.be.empty
  })

  it('Expect tint to return tint with full bright value', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    }

    const tint = await lib.fromRGB({
      input: rgb,
      output: 'tint'
    })

    expect(tint.data).to.not.be.empty
    expect(tint.data[1].l).to.be.equal(100)
  })

  it('Expect tint to return tint with full dark value', async () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    }

    const tint = await lib.fromRGB({
      input: rgb,
      output: 'tint'
    })

    expect(tint.data).to.not.be.empty
    expect(tint.data[1].l).to.be.equal(10)
  })

  it('Expect to throw when no value is passed', async () => {
    try {
      await lib.fromRGB({
        output: 'tint'
      })
    } catch (e) {
      expect(e.err).to.be.equal('Missing arguments')
    }
  })
})