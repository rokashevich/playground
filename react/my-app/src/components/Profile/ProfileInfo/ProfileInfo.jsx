import React from 'react'
import Preloader from '../../common/preloader/Preloader'
import s from './ProfileInfo.module.css'
import ProfileStatus from './ProfileStatus'

const ProfileInfo = props => {
  if (!props.profile) {
    return <Preloader />
  }
  return (
    <div className={s.descriptionBlock}>
      <div>
        <img alt='ava' src={props.profile.photos.large} />
      </div>
      <div>
        <ProfileStatus status={'xxx'} />
      </div>
      <div>aboutMe</div>
      <div>{props.profile.aboutMe}</div>
      {Object.entries(props.profile.contacts).map(([key, val]) => (
        <>
          <div>{key}</div>
          <div>{val}</div>
        </>
      ))}
      <div>lookingForAJob</div>
      <div>{props.profile.lookingForAJob}</div>
      <div>lookingForAJobDescription</div>
      <div>{props.profile.lookingForAJobDescription}</div>
      <div>fullName</div>
      <div>{props.profile.fullName}</div>
      <div>userId</div>
      <div>{props.profile.userId}</div>
    </div>
  )
}

export default ProfileInfo
