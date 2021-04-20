import React from 'react'
import preloader from '../../../assets/images/preloader.svg'
let Preloader = props => {
  return (
    <div>
      <img
        alt='preloader'
        src={preloader}
        style={{ backgroundColor: 'blue' }}
      />
    </div>
  )
}
export default Preloader
