import React from 'react'
import Preloader from '../../common/preloader/Preloader'
import s from './ProfileInfo.module.css'

const ProfileInfo = props => {
  if (!props.profile) {
    return <Preloader />
  }
  return (
    <div>
      <div className={s.descriptionBlock}>
        <img alt='ava' src={props.profile.photos.small} />
        <img alt='ava' src={props.profile.photos.large} />
      </div>
      <div>aboutMe: {props.profile.aboutMe}</div>
      {Object.entries(props.profile.contacts).map(([key, val]) => (
        <div>
          Contact {key} {val}
        </div>
      ))}
      <div>lookingForAJob: {props.profile.lookingForAJob}</div>
      <div>
        lookingForAJobDescription: {props.profile.lookingForAJobDescription}
      </div>
      <div>fullName: {props.profile.fullName}</div>
      <div>userId: {props.profile.userId}</div>
    </div>
  )
}

export default ProfileInfo
